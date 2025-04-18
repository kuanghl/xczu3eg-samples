﻿/************************************************************************************//**
*\n  @file       xlnk_mem.c
*\n  @brief      xlnk_mem
*\n  @details
*\n -------------------------------------------------------------------------
*\n  文件说明：
*\n       1.  配置设备树：    	
*\n       	jimu_mem {   
*\n       		compatible = "jimu,mem";
*\n       		path = "jimu.mem";
*\n       	};
*\n       
*\n       2.  生成设备节点名          /dev/jimu.mem
*\n       
*\n -------------------------------------------------------------------------
*\n  版本:   修改人:   修改日期:       描述:
*\n  V1.0    罗先能    2018.3.22       创建
*\n 
****************************************************************************************/

/***************************************************************************************
 * 头文件
****************************************************************************************/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <asm/cacheflush.h>
#include <linux/io.h>
#include <linux/dma-buf.h>

#include <linux/string.h>

#include <linux/uaccess.h>

#include <linux/dmaengine.h>
#include <linux/completion.h>
#include <linux/wait.h>

#include <linux/device.h>
#include <linux/init.h>
#include <linux/cdev.h>

#include <linux/sched.h>
#include <linux/pagemap.h>
#include <linux/errno.h>	/* error codes */
#include <linux/dma-mapping.h>  /* dma */
#include <linux/of.h>
#include <linux/list.h>
#include <linux/dma/xilinx_dma.h>
#include <linux/uio_driver.h>
#include <asm/cacheflush.h>
#include <linux/semaphore.h>
#include <linux/ioctl.h>
#include <linux/stddef.h>

#include "xlnk-sysdef.h"
//#include "xlnk-config.h"



/***************************************************************************************
 * 宏定、常量、结构定义
****************************************************************************************/
//#include "xlnk-ioctl.h"
#define XLNK_IOC_MAGIC 		'L'
#define XLNK_IOCRESET		_IO(XLNK_IOC_MAGIC, 0)
#define XLNK_IOCALLOCBUF	_IOWR(XLNK_IOC_MAGIC, 1, unsigned long)  // 申请内存
#define XLNK_IOCFREEBUF		_IOWR(XLNK_IOC_MAGIC, 2, unsigned long)  // 释放内存
#define XLNK_IOCCACHECTRL	_IOWR(XLNK_IOC_MAGIC, 3, unsigned long)      // 刷新cache
#define XLNK_IOCRECRES		_IOWR(XLNK_IOC_MAGIC, 4, unsigned long)     // free all buffers
#define XLNK_IOC_MAXNR		10




#define DRIVER_VERSION  "0.2"
#define DRIVER_NAME     "jimu.mem"
#define DEVICE_NAME     "jimu.mem"
#define CLASS_NAME 		"jimu.mem"
#define MODULE_NAME 	"jimu.mem"

#define MAX_XLNK_DMAS 	128

#define XLNK_FLAG_COHERENT		0x00000001
#define XLNK_FLAG_KERNEL_BUFFER		0x00000002
#define XLNK_FLAG_DMAPOLLING		0x00000004
#define XLNK_FLAG_IOMMU_VALID		0x00000008
#define XLNK_FLAG_PHYSICAL_ADDR		0x00000100
#define XLNK_FLAG_VIRTUAL_ADDR		0x00000200
#define XLNK_FLAG_MEM_ACQUIRE		0x00001000
#define XLNK_FLAG_MEM_RELEASE		0x00002000
#define CF_FLAG_CACHE_FLUSH_INVALIDATE	0x00000001
#define CF_FLAG_PHYSICALLY_CONTIGUOUS	0x00000002
#define CF_FLAG_DMAPOLLING		0x00000004

enum xlnk_dma_direction {
	XLNK_DMA_BI = 0,
	XLNK_DMA_TO_DEVICE = 1,
	XLNK_DMA_FROM_DEVICE = 2,
	XLNK_DMA_NONE = 3,
};

struct xlnk_dma_transfer_handle {
	dma_addr_t dma_addr;
	unsigned long transfer_length;
	void *kern_addr;
	unsigned long user_addr;
	enum dma_data_direction transfer_direction;
	struct scatterlist *sg_list;
	int sg_list_size;
	int sg_effective_length;
	int flags;
	struct dma_chan *channel;
	dma_cookie_t dma_cookie;
	struct dma_async_tx_descriptor *async_desc;
	struct completion completion_handle;
};

struct xlnk_dmabuf_reg {
	xlnk_int_type dmabuf_fd;
	xlnk_intptr_type user_vaddr;
	struct dma_buf *dbuf;
	struct dma_buf_attachment *dbuf_attach;
	struct sg_table *dbuf_sg_table;
	struct scatterlist *sg_list;
	int sg_list_cnt;
	int is_mapped;
	int dma_direction;
	struct list_head list;
};

union xlnk_args 
{
	// 内存申请/释放
	struct __attribute__ ((__packed__)) 
	{
		u32 size;                       // [in]  长度bytesbytes;
		u32 cacheable;                  // [in]   0/1 : no cached / cached
		s32 id; 					    // [out]  索引号;    freebuf时只需要该参数
		dma_addr_t phys_addr;           // [out]  物理地址
		dma_addr_t user_addr;           // [user] kernel not used;
	} allocbuf;

	// Cache flash/invalid
	struct __attribute__ ((__packed__)) 
	{
		u32 size;                       // [in]   长度bytes
		s32 action;                     // [in]   0:DMA_TO_DEVICE(flash); 1:DMA_FROM_DEVICE(invalid)
		dma_addr_t phys_addr;                  // [in]   物理地址
		dma_addr_t user_addr;                  // [in]   用户地址
	} cachecontrol;
};


/***************************************************************************************
 * 私有变量声明、定义
****************************************************************************************/
static struct platform_device *xlnk_pdev;
static struct device *xlnk_dev;

static struct cdev xlnk_cdev;

static struct class *xlnk_class;

static s32 driver_major;

static char *driver_name = DRIVER_NAME;
static char *dev_path = DRIVER_NAME;



static void *xlnk_dev_buf;
static ssize_t xlnk_dev_size;
static int xlnk_dev_vmas;

#define XLNK_BUF_POOL_SIZE	4096
static unsigned int xlnk_bufpool_size = XLNK_BUF_POOL_SIZE;
static void *xlnk_bufpool[XLNK_BUF_POOL_SIZE];
static void *xlnk_bufpool_alloc_point[XLNK_BUF_POOL_SIZE];
static xlnk_intptr_type xlnk_userbuf[XLNK_BUF_POOL_SIZE];
static int xlnk_buf_process[XLNK_BUF_POOL_SIZE];
static dma_addr_t xlnk_phyaddr[XLNK_BUF_POOL_SIZE];
static size_t xlnk_buflen[XLNK_BUF_POOL_SIZE];
static unsigned int xlnk_bufcacheable[XLNK_BUF_POOL_SIZE];
static spinlock_t xlnk_buf_lock;

static raw_spinlock_t raw_lock;


/* only used with standard DMA mode */
static struct page **xlnk_page_store;
static int xlnk_page_store_size;

//LIST_HEAD(xlnk_dmabuf_list);

static u64 dma_mask = 0xFFFFFFFFUL;


struct xlnk_device_pack
{
	char name[64];
	struct platform_device pdev;
	struct resource res[8];
	struct uio_info *io_ptr;
	int refs;



};

static struct xlnk_device_pack *xlnk_devpacks[MAX_XLNK_DMAS];
static struct semaphore xlnk_devpack_sem;


/***************************************************************************************
 * 私有函数声明、定义
****************************************************************************************/
#if 1
static void xlnk_vma_open(struct vm_area_struct *vma)
{
	xlnk_dev_vmas++;
}

static void xlnk_vma_close(struct vm_area_struct *vma)
{
	xlnk_dev_vmas--;
}

static const struct vm_operations_struct xlnk_vm_ops =
{
	.open = xlnk_vma_open,
	.close = xlnk_vma_close,
};
#endif



#if 1
//----------------------------------------------------
// 将xlnk-config.c/h文件合并，并设置为static，
//  避免同内核中文件冲突
//----------------------------------------------------
enum xlnk_config_dma {
	xlnk_config_dma_manual,
	xlnk_config_dma_standard,
	xlnk_config_dma_size,
};

enum xlnk_config_valid {
	xlnk_config_valid_dma_type = 0,

	xlnk_config_valid_size = 1,
};

struct __attribute__ ((__packed__)) xlnk_config_block
{
	xlnk_byte_type valid_mask[xlnk_config_valid_size];

	xlnk_enum_type dma_type;
};


static struct xlnk_config_block system_config;

static void xlnk_config_clear_block(struct xlnk_config_block *config_block)
{
	int i;

	for (i = 0; i < xlnk_config_valid_size; i++)
		config_block->valid_mask[i] = 0;
}

static void xlnk_init_config(void)
{
	int i;

	system_config.dma_type = xlnk_config_dma_manual;

	for (i = 0; i < xlnk_config_valid_size; i++)
		system_config.valid_mask[i] = 1;
}

static int xlnk_set_config(const struct xlnk_config_block *config_block)
{
#define XLNK_CONFIG_HELP(x) \
	if (config_block->valid_mask[xlnk_config_valid_##x]) \
	system_config.x = config_block->x

	XLNK_CONFIG_HELP(dma_type);

#undef XLNK_CONFIG_HELP
	return 0;
}

static void xlnk_get_config(struct xlnk_config_block *config_block)
{
	*config_block = system_config;
}

static int xlnk_config_dma_type(enum xlnk_config_dma type)
{
	if (system_config.dma_type == type)
		return 1;
	return 0;
}
#endif



#if 1
static int xlnk_init_bufpool(void)
{
	unsigned int i;

	spin_lock_init(&xlnk_buf_lock);
	xlnk_dev_buf = kmalloc(8192, GFP_KERNEL | GFP_DMA);
	*((char *)xlnk_dev_buf) = '\0';

	if (!xlnk_dev_buf)
	{
		dev_err(xlnk_dev, "%s: malloc failed\n", __func__);
		return -ENOMEM;
	}

	xlnk_bufpool[0] = xlnk_dev_buf;
	for (i = 1; i < xlnk_bufpool_size; i++)
		xlnk_bufpool[i] = NULL;

	return 0;
}



static void xlnk_devpacks_init(void)
{
	unsigned int i;

	sema_init(&xlnk_devpack_sem, 1);
	for (i = 0; i < MAX_XLNK_DMAS; i++)
		xlnk_devpacks[i] = NULL;
}

static void xlnk_devpacks_delete(struct xlnk_device_pack *devpack)
{
	unsigned int i;

	for (i = 0; i < MAX_XLNK_DMAS; i++)
	{
		if (xlnk_devpacks[i] == devpack)
			xlnk_devpacks[i] = NULL;
	}
}

static void xlnk_devpacks_add(struct xlnk_device_pack *devpack)
{
	unsigned int i;

	devpack->refs = 1;
	for (i = 0; i < MAX_XLNK_DMAS; i++)
	{
		if (!xlnk_devpacks[i])
		{
			xlnk_devpacks[i] = devpack;
			break;
		}
	}
}

static struct xlnk_device_pack *xlnk_devpacks_find(xlnk_intptr_type base)
{
	unsigned int i;

	for (i = 0; i < MAX_XLNK_DMAS; i++)
	{
		if (xlnk_devpacks[i] &&
		    xlnk_devpacks[i]->res[0].start == base)
			return xlnk_devpacks[i];
	}
	return NULL;
}

static void xlnk_devpacks_free(xlnk_intptr_type base)
{
	struct xlnk_device_pack *devpack;

	down(&xlnk_devpack_sem);
	devpack = xlnk_devpacks_find(base);
	if (!devpack)
	{
		up(&xlnk_devpack_sem);
		return;
	}
	devpack->refs--;
	if (devpack->refs)
	{
		up(&xlnk_devpack_sem);
		return;
	}
	if (xlnk_config_dma_type(xlnk_config_dma_standard))
	{
		if (devpack->io_ptr)
			uio_unregister_device(devpack->io_ptr);
		if (strcmp(devpack->pdev.name, "xilinx-axidma") != 0)
			platform_device_unregister(&devpack->pdev);
	}
	else
	{
		platform_device_unregister(&devpack->pdev);
	}
	xlnk_devpacks_delete(devpack);
	kfree(devpack);
	up(&xlnk_devpack_sem);
}

static void xlnk_devpacks_free_all(void)
{
	struct xlnk_device_pack *devpack;
	unsigned int i;

	for (i = 0; i < MAX_XLNK_DMAS; i++)
	{
		devpack = xlnk_devpacks[i];
		if (devpack)
		{
			if (devpack->io_ptr)
			{
				uio_unregister_device(devpack->io_ptr);
				kfree(devpack->io_ptr);
			}
			else
			{
				platform_device_unregister(&devpack->pdev);
			}
			xlnk_devpacks_delete(devpack);
			kfree(devpack);
		}
	}
}
#endif



// 1. init_config为manual
// 读取dtc中的参数 config-dma-type，并修改默认参数
static void xlnk_load_config_from_dt(struct platform_device *pdev)
{
	//const char *dma_name = NULL;
	//struct xlnk_config_block block;

	xlnk_init_config();
}


#if 2
static int xlnk_buf_findnull(void)
{
	int i;

	for (i = 1; i < xlnk_bufpool_size; i++)
	{
		if (!xlnk_bufpool[i])
			return i;
	}

	return 0;
}


static int xlnk_buf_find_by_phys_addr(xlnk_intptr_type addr)
{
	int i;

	for (i = 1; i < xlnk_bufpool_size; i++)
	{
		if (xlnk_bufpool[i] && 
			xlnk_phyaddr[i] <= addr && xlnk_phyaddr[i] + xlnk_buflen[i] > addr)
			return i;
	}

	return 0;
}

static int xlnk_buf_find_by_user_addr(xlnk_intptr_type addr, int pid)
{
	int i;

	for (i = 1; i < xlnk_bufpool_size; i++)
	{
		if (xlnk_bufpool[i] &&
		    xlnk_buf_process[i] == pid &&
		    xlnk_userbuf[i] <= addr &&
		    xlnk_userbuf[i] + xlnk_buflen[i] > addr)
			return i;
	}

	return 0;
}


/**
 * allocate and return an id
 * id must be a positve number
 */
static int xlnk_allocbuf(unsigned int len, unsigned int cacheable)
{
	int id;
	void *kaddr;
	dma_addr_t phys_addr_anchor;

	if (cacheable)
		kaddr = dma_alloc_coherent(xlnk_dev,
		                              len,
		                              &phys_addr_anchor,
		                              GFP_KERNEL |
		                              GFP_DMA);  //|
		                             // GFP_USER // __GFP_REPEAT);
	else
		kaddr = dma_alloc_coherent(xlnk_dev,
		                           len,
		                           &phys_addr_anchor,
		                           GFP_KERNEL |
		                           GFP_DMA);   //|
								   // GFP_USER //__GFP_REPEAT);
	if (!kaddr)
		return -ENOMEM;

	spin_lock(&xlnk_buf_lock);
	id = xlnk_buf_findnull();
	if (id > 0 && id < XLNK_BUF_POOL_SIZE)
	{
		xlnk_bufpool_alloc_point[id] = kaddr;
		xlnk_bufpool[id] 			= kaddr;
		xlnk_buflen[id] 			= len;
		xlnk_bufcacheable[id] 		= cacheable;
		xlnk_phyaddr[id] 			= phys_addr_anchor;
	}
	spin_unlock(&xlnk_buf_lock);

	if (id <= 0 || id >= XLNK_BUF_POOL_SIZE)
		return -ENOMEM;


	//pr_err("<xlnk_mem.c> kaddr=0x%llx, phys_addr_anchor=0x%llx\n", (dma_addr_t)kaddr, phys_addr_anchor);
	return id;
}



static int xlnk_allocbuf_ioctl(struct file *filp,
                               unsigned int code,
                               unsigned long args)
{
	union xlnk_args temp_args;
	int status;
	xlnk_int_type id;

	status = copy_from_user(&temp_args, (void __user *)args,
	                        sizeof(union xlnk_args));

	if (status)
		return -ENOMEM;

	id = xlnk_allocbuf(temp_args.allocbuf.size,
	                   temp_args.allocbuf.cacheable);

	if (id <= 0)
		return -ENOMEM;

	temp_args.allocbuf.id = id;
	temp_args.allocbuf.phys_addr = (xlnk_phyaddr[id]);
	status = copy_to_user((void __user *)args, &temp_args,
	                      sizeof(union xlnk_args));

	return status;
}

static int xlnk_freebuf(int id)
{
	void *alloc_point;
	dma_addr_t p_addr;
	size_t buf_len;
	int cacheable;

	if (id <= 0 || id >= xlnk_bufpool_size)
		return -ENOMEM;

	if (!xlnk_bufpool[id])
		return -ENOMEM;

	spin_lock(&xlnk_buf_lock);
	alloc_point = xlnk_bufpool_alloc_point[id];
	p_addr = xlnk_phyaddr[id];
	buf_len = xlnk_buflen[id];
	xlnk_bufpool[id] = NULL;
	xlnk_phyaddr[id] = (dma_addr_t)NULL;
	xlnk_buflen[id] = 0;
	cacheable = xlnk_bufcacheable[id];
	xlnk_bufcacheable[id] = 0;
	spin_unlock(&xlnk_buf_lock);

	if (cacheable)
		dma_free_coherent(xlnk_dev,
		                     buf_len,
		                     alloc_point,
		                     p_addr);
	else
		dma_free_coherent(xlnk_dev,
		                  buf_len,
		                  alloc_point,
		                  p_addr);

	return 0;
}

static void xlnk_free_all_buf(void)
{
	int i;

	for (i = 1; i < xlnk_bufpool_size; i++)
		xlnk_freebuf(i);
}

static int xlnk_recover_resource(void)
{
	xlnk_free_all_buf();
	return 0;
}

static int xlnk_freebuf_ioctl(struct file *filp, unsigned int code, unsigned long args)
{
	union xlnk_args temp_args;
	int status;
	int id;

	status = copy_from_user(&temp_args, (void __user *)args,
	                        sizeof(union xlnk_args));

	if (status)
		return -ENOMEM;

	id = temp_args.allocbuf.id;
	return xlnk_freebuf(id);
}




// invalidate all D-Cache by DCISW "Invalidate data* cache line by set/way"
static void invalidate_cache_all(void)
{
	
	__asm__ __volatile__  (
	"    stmfd	sp!, {r4-r5, r7, r9-r11, lr}                                 \n"
    "    mov     r0, #0                                                       \n"
    "    mcr     p15, 2, r0, c0, c0, 0                                        \n"
    "    mrc     p15, 1, r0, c0, c0, 0                                        \n"
    "                                                                         \n"
    "    movw    r1, #0x7fff                                                  \n"
    "    and     r2, r1, r0, lsr #13                                          \n"
    "                                                                         \n"
    "    movw    r1, #0x3ff                                                   \n"
    "                                                                         \n"
    "    and     r3, r1, r0, lsr #3      @ NumWays - 1                        \n"
    "    add     r2, r2, #1              @ NumSets                            \n"
    "                                                                         \n"
    "    and     r0, r0, #0x7                                                 \n"
    "    add     r0, r0, #4              @ SetShift                           \n"
    "                                                                         \n"
    "    clz     r1, r3                  @ WayShift                           \n"
    "    add     r4, r3, #1              @ NumWays                            \n"
	" 1: sub     r2, r2, #1              @ NumSets--                          \n"
    "    mov     r3, r4                  @ Temp = NumWays                     \n"
    "                                                                         \n"
	" 2: subs    r3, r3, #1              @ Temp--                             \n"
    "    mov     r5, r3, lsl r1                                               \n"
    "    mov     r6, r2, lsl r0                                               \n"
    "    orr     r5, r5, r6                                                   \n"
    "    mcr     p15, 0, r5, c7, c6, 2   @ DCISW                              \n"
    "    bgt     2b                                                           \n"
    "    cmp     r2, #0                                                       \n"
    "    bgt     1b                                                           \n"
    "    dsb     st                                                           \n"
    "    isb                                                                  \n"
    "    ldmfd   sp!, {r4-r5, r7, r9-r11, lr}                                 \n"
	);
}



static int xlnk_cachecontrol_ioctl(struct file *filp, unsigned int code, unsigned long args)
{
	union xlnk_args temp_args;
	int status, size;
	void *kaddr;
	xlnk_intptr_type paddr;
//	int buf_id;
	int dir;

	status = copy_from_user(&temp_args, (void __user *)args, sizeof(union xlnk_args));
	if (status)
	{
		dev_err(xlnk_dev, "Error in copy_from_user. status = %d\n", status);
		return -ENOMEM;
	}

	dir   = temp_args.cachecontrol.action;
	size  = temp_args.cachecontrol.size;
	paddr = temp_args.cachecontrol.phys_addr;
	kaddr = (void*)temp_args.cachecontrol.user_addr;

//	flush_cache_all();
//	if (dir == 0) { outer_flush_range(paddr, paddr + size); }
//	else          { outer_inv_range(paddr, paddr + size);   }
//	return 0;


 /*** Arm32 / Arm64控制方法不同 ***/
//#if XLNK_SYS_BIT_WIDTH == 32  
//	__cpuc_flush_dcache_area(kaddr, size);
//	outer_flush_range(paddr, paddr + size);
//	if (temp_args.cachecontrol.action == 1)
//		outer_inv_range(paddr, paddr + size);
//#else
//	if (dir == 1)
//		__dma_map_area(kaddr, size, DMA_FROM_DEVICE);
//	else
//		__dma_map_area(kaddr, size, DMA_TO_DEVICE);
//#endif
	return 0;


}



/* This function provides IO interface to the bridge driver. */
static long xlnk_ioctl(struct file *filp, unsigned int code, unsigned long args)
{
	if (_IOC_TYPE(code) != XLNK_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(code) > XLNK_IOC_MAXNR)
		return -ENOTTY;

	/* some sanity check */
	switch (code)
	{
		// 内存申请、释放、全部释放
		case XLNK_IOCALLOCBUF:
			return xlnk_allocbuf_ioctl(filp, code, args);
		case XLNK_IOCFREEBUF:
			return xlnk_freebuf_ioctl(filp, code, args);
		case XLNK_IOCRECRES:
			return xlnk_recover_resource();

		// cache flash/invalid
		case XLNK_IOCCACHECTRL:
			return xlnk_cachecontrol_ioctl(filp, code, args);

		default:
			return -EINVAL;
	}
}
#endif


/* This function maps kernel space memory to user space memory. */
static int xlnk_mmap(struct file *filp, struct vm_area_struct *vma)
{
	int buf_id;
	int status;

	int paddr = vma->vm_pgoff << PAGE_SHIFT;
	buf_id = xlnk_buf_find_by_phys_addr(paddr);
	if (buf_id == 0)
	{
		pr_err("xlnk_mmap failed with code %d\n", EAGAIN);
		return -EAGAIN;
	}
	
	if (xlnk_bufcacheable[buf_id] == 0) {
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	}
	else {
		//vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}
	
	status = remap_pfn_range(vma, vma->vm_start,
	                         xlnk_phyaddr[buf_id] >> PAGE_SHIFT,
	                         vma->vm_end - vma->vm_start,
	                         vma->vm_page_prot);
	
	xlnk_userbuf[buf_id] 	= vma->vm_start;
	xlnk_buf_process[buf_id] = current->pid;

	if (status)
	{
		pr_err("xlnk_mmap failed with code %d\n", EAGAIN);
		return -EAGAIN;
	}

	xlnk_vma_open(vma);
	vma->vm_ops = &xlnk_vm_ops;
	vma->vm_private_data = xlnk_bufpool[buf_id];

	return 0;
}


/*
 * This function is called when an application opens handle to the
 * bridge driver.
 */
static int xlnk_open(struct inode *ip, struct file *filp)
{
	if ((filp->f_flags & O_ACCMODE) == O_WRONLY)
		xlnk_dev_size = 0;

	return 0;
}


/*
 * This function is called when an application closes handle to the bridge
 * driver.
 */
static int xlnk_release(struct inode *ip, struct file *filp)
{
	return 0;
}


static const struct file_operations xlnk_fops =
{
	.open 	 = xlnk_open,
	.release = xlnk_release,
	.unlocked_ioctl = xlnk_ioctl,
	.mmap = xlnk_mmap,
};



#if 1
static int mem_remove(struct platform_device *pdev)
{
	dev_t devno;

	kfree(xlnk_dev_buf);
	xlnk_dev_buf = NULL;

	devno = MKDEV(driver_major, 0);
	cdev_del(&xlnk_cdev);
	unregister_chrdev_region(devno, 1);
	if (xlnk_class)
	{
		/* remove the device from sysfs */
		device_destroy(xlnk_class, MKDEV(driver_major, 0));
		class_destroy(xlnk_class);
	}

	return 0;
}

static int mem_probe(struct platform_device *pdev)
{
	int err;
	int ret;
	dev_t dev = 0;
	struct device_node 	*np;

	xlnk_dev_buf = NULL;
	xlnk_dev_size = 0;
	xlnk_dev_vmas = 0;

	dev_info(&pdev->dev, "xxx_probe() ...\n");
	dev_info(&pdev->dev, "build %s,%s \n", __DATE__, __TIME__);

	np = pdev->dev.of_node;
	ret = of_property_read_string(np, "path", (const char**)&(dev_path));
	if (ret)
	{
		dev_err(xlnk_dev, "not find 'path' in device tree \n");
	}

	xlnk_page_store_size = 1024;
	xlnk_page_store = vmalloc(sizeof(struct page *) * xlnk_page_store_size);
	if (!xlnk_page_store)
	{
		dev_err(xlnk_dev, "failed to allocate memory for page store\n");
		err = -ENOMEM;
		goto err1;
	}
	err = alloc_chrdev_region(&dev, 0, 1, driver_name);
	if (err)
	{
		dev_err(xlnk_dev, "%s: Can't get major %d\n",
		       __func__, driver_major);
		goto err1;
	}

	cdev_init(&xlnk_cdev, &xlnk_fops);
	xlnk_cdev.owner = THIS_MODULE;
	err = cdev_add(&xlnk_cdev, dev, 1);
	if (err)
	{
		dev_err(xlnk_dev, "%s: Failed to add XLNK device\n",
		       __func__);
		goto err3;
	}

	/* udev support */
	xlnk_class = class_create(THIS_MODULE,  CLASS_NAME);
	if (IS_ERR(xlnk_class))
	{
		dev_err(xlnk_dev, "%s: Error creating xlnk class\n", __func__);
		goto err3;
	}
	driver_major = MAJOR(dev);
	dev_info(&pdev->dev, "Major %d\n", driver_major);

	device_create(xlnk_class, NULL, MKDEV(driver_major, 0), NULL, DEVICE_NAME);

	xlnk_init_bufpool();

	xlnk_pdev = pdev;
	xlnk_dev = &pdev->dev;

	xlnk_load_config_from_dt(pdev);
	xlnk_devpacks_init();

	dev_info(&pdev->dev, "/dev/%s create ok\n", DEVICE_NAME);
	return 0;
err3:
	cdev_del(&xlnk_cdev);
	unregister_chrdev_region(dev, 1);
err1:
	pr_err("xxx_probe error!\n");
	return err;
}


#if 0
static void __exit xlnk_exit(void)
{
	axidma_remove(NULL);
}

static int __init xlnk_init(void)
{
	axidma_probe(NULL);
	return 0;
}
module_init(xlnk_init);
module_exit(xlnk_exit);
#endif


#if 2
static const struct of_device_id dma_match[] =
{
	{ .compatible = "jimu,mem", },
	{}
};
MODULE_DEVICE_TABLE(of, dma_match);


static struct platform_driver  mem_driver =
{
	.probe	= mem_probe,
	.remove = mem_remove,
	.driver =
	{
		.owner = THIS_MODULE,
		.name = MODULE_NAME,
		.of_match_table = dma_match,
	},
};
module_platform_driver(mem_driver);
#endif
#endif

MODULE_AUTHOR("wuhan jimu, Inc.");
MODULE_DESCRIPTION("Xilinx simple AXI DMA driver");
MODULE_LICENSE("GPL v2");

//MODULE_AUTHOR("jimu, Inc.");
//MODULE_DESCRIPTION("jimu driver");
//MODULE_LICENSE("GPL");




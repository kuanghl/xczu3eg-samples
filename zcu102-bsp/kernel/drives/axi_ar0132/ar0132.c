/***********************************************************************************************//**
*\n  @file       ar0132.c
*\n  @brief      ar0132 驱动
*\n  @details
*\n -----------------------------------------------------------------------------------
*\n  文件说明：
*\n       1. ar0132 驱动
*\n       2. PL使用2个EMIO口作为SCL/SDA; 软件通过AXI接口直接控制，模拟i2c接口。
*\n		  3. 地址16bit， 数据16bit,
*\n       
*\n -----------------------------------------------------------------------------------
*\n  版本:  	 修改人:       修改日期:        	描述:
*\n  V0.1    罗先能        2019.7.1        创建
*\n 
***************************************************************************************************/

/**************************************************************************************************
* 头文件
***************************************************************************************************/
#include <linux/bitops.h>
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/of_gpio.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/irqdomain.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/clk.h>

#include <linux/cdev.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/miscdevice.h>
#include <linux/pci.h>
#include <linux/wait.h>
#include <linux/fs.h>



/**************************************************************************************************
* 宏定义、结构定义
***************************************************************************************************/
// 设备树
// jimu_camera {
// 	compatible = "jimu,camera";
// 	reg = < 0x41200000 0x1000>;
// 	path = "jimu.camera";
// };

#define DRIVER_NAME	  "jimu.camera"
#define DEVICE_NAME	  "jimu.camera"
#define CLASS_NAME	  "jimu.camera"
#define MODULE_NAME	  "jimu.camera"

// 0x4120020
//SCL_I    	:  GP_I  bit[0]
//SDA_I    	:  GP_I  bit[1]
// 0x4120024
//SCL_O  	:  GP_O  bit[0]
//SCL_T  	:  GP_O  bit[1]   // 1= in, 0 = out
//SDA_O  	:  GP_O  bit[2]
//SDA_T  	:  GP_O  bit[3]   // 1= in, 0 = out
#define  SCL_I     (1 << 0)
#define  SDA_I     (1 << 1)

#define  SCL_O     (1 << 0)
#define  SCL_T     (1 << 1)   // 1= in, 0 = out
#define  SDA_O     (1 << 2)
#define  SDA_T     (1 << 3)   // 1= in, 0 = out

#define DEVICE_ID  (0x10 << 1)  // bit0为R/W


/**************************************************************************************************
* 全局变量声明、定义
***************************************************************************************************/


/**************************************************************************************************
* 私有变量声明、定义
***************************************************************************************************/
typedef struct ov5640_device
{
	int  used;
	char 			*name;
	char 			*path;
	spinlock_t gpio_lock;

	// driver option
	dev_t			devno;
	struct cdev    	cdev;
	struct class  	*class;
	struct device 	*dev;

	struct resource *reg;      // 寄存器
	void __iomem 	*base;     // 基地址
	void __iomem 	*in_base;  // 读取
	void __iomem 	*out_base; // 写入

} ov5640_device;


/**************************************************************************************************
* 私有函数声明、定义
***************************************************************************************************/


/**************************************************************************************************
* 全局函数声明、定义
***************************************************************************************************/





#if 1

#define read_reg(offset)		 readl(offset)
#define write_reg(offset, val)	 writel(val, offset)



#if 3


// SCL输出电压
#define  SCL_OUT(val) \
	do{ \
		value  = read_reg(this->out_base);   	\
		value  = value & (~SCL_T)  & (~SCL_O); 	\
		value |= val ? SCL_O : 0;             \
		write_reg(this->out_base, value);     \
	} while(0)

// SDA输出电压
#define  SDA_OUT(val) \
	do{ \
		value  = read_reg(this->out_base);    \
		value  = value & (~SDA_T)  & (~SDA_O);\
		value |= val ? SDA_O : 0;             \
		write_reg(this->out_base, value);     \
	} while(0)

// 读取SDA电压
static inline u32 SDA_IN(struct ov5640_device *this)
{
	u32 value;

	value  = read_reg(this->in_base);
	value &= SDA_I;

	return value ? 1 : 0;
}

//设置SDA为输出
#define  SET_SDA_OUT() \
	do{ \
		value  = read_reg(this->out_base);    \
		value &= ~SDA_T;                      \
		write_reg(this->out_base, value);     \
	} while(0)

// 设置SDA为输入
#define  SET_SDA_IN()  \
	do{ \
		value  = read_reg(this->out_base);    \
		value |= SDA_T;                       \
		write_reg(this->out_base, value);     \
	} while(0)


static void i2c_delay(void)
{
	volatile int loop = 1000;
	while (loop--);
}

static void i2c_start(struct ov5640_device *this)
{
	u32 value;

	SDA_OUT(1);     //数据线高电平
	SCL_OUT(1);	    //在时钟线高的时候数据线由高至低
	i2c_delay();
	SDA_OUT(0);
	i2c_delay();
	SCL_OUT(0);	    //数据线恢复低电平，单操作函数必要
}

//SCCB停止信号
static void i2c_stop(struct ov5640_device *this)
{
	u32 value;

	SDA_OUT(0);
	i2c_delay();
	SCL_OUT(1);
	i2c_delay();
	SDA_OUT(1);
	i2c_delay();
}

static void i2c_no_ack(struct ov5640_device *this)
{
	u32 value;

	i2c_delay();
	SDA_OUT(1);
	SCL_OUT(1);
	i2c_delay();
	SCL_OUT(0);
	i2c_delay();
	SDA_OUT(0);
	i2c_delay();
}

//i2c,写入一个字节
//返回值:0,成功;-1,失败.
int i2c_write_byte(struct ov5640_device *this,  u8 dat)
{
	u32 value;
	u8 j,res;

	for (j=0; j<8; j++)
	{
		if (dat & 0x80)
			SDA_OUT(1);
		else SDA_OUT(0);
		dat <<= 1;
		i2c_delay();
		SCL_OUT(1);
		i2c_delay();
		SCL_OUT(0);
	}
	SET_SDA_IN();		    // 设置SDA为输入
	i2c_delay();
	SCL_OUT(1);			// 接收第九位,以判断是否发送成功
	i2c_delay();
	if (SDA_IN(this))
		res = -1;  		//SDA=1发送失败，返回-1
	else
		res =  0;  		//SDA=0发送成功，返回0
	SCL_OUT(0);
	SET_SDA_OUT();		//设置SDA为输出

	return res;
}

//i2c 读取一个字节
//在SCL的上升沿,数据锁存
//返回值:读到的数据
u8 i2c_read_byte(struct ov5640_device *this)
{
	u32 value;

	u8 temp=0,j;
	SET_SDA_IN();		//设置SDA为输入
	for (j=8; j>0; j--) 	//循环8次接收数据
	{
		i2c_delay();
		SCL_OUT(1);
		temp=temp<<1;
		if (SDA_IN(this)) temp++;
		i2c_delay();
		SCL_OUT(0);
	}
	SET_SDA_OUT();		//设置SDA为输出
	return temp;
}
#endif



// 读寄存器,读取2bytes的数据(低地址存放高字节)
static int reg_read(struct ov5640_device *this, u16 reg, u8 *val)
{
	int ret = 2;
	u8 value;

	
	// 写地址
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID)) 		ret = -1;
	if (i2c_write_byte(this, reg>>8))			ret = -1;
	if (i2c_write_byte(this, reg))				ret = -1;
	i2c_stop(this);

	// 读取第1个字节(高字节)
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID | 0X01)) ret = -1;
	value = i2c_read_byte(this);
	i2c_no_ack(this);
	i2c_stop(this);
	*(val+1) = value;

	// 读取第2个字节（低字节）
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID | 0X01)) ret = -1;
	value = i2c_read_byte(this);
	i2c_no_ack(this);
	i2c_stop(this);
	*(val) = value;

	return ret;  // 读到2字节
}

// 写寄存器,写2bytes的数据(低地址存放高字节)
static int reg_write(struct ov5640_device *this, u16 address, u16 data)
{
	u32 value;

	int ret = 2;

	i2c_start(this); 								//启动SCCB传输
	if (i2c_write_byte(this, DEVICE_ID)) 		ret =-1;	//写器件ID
	if (i2c_write_byte(this, address>>8))	  	ret =-1;	//写寄存器高8位地址
	if (i2c_write_byte(this, address))			ret =-1;	//写寄存器低8位地址
	
	//写数据
	if (i2c_write_byte(this, (u8)(data>>8)))	ret =-1; 	// 高字节
	if (i2c_write_byte(this, (u8)data))			ret =-1;    // 低字节
	i2c_stop(this);

	return	ret;  // 写入2bytes
}


static ssize_t camera_read(struct file *file, char __user *buf, size_t count,
                           loff_t *offset)
{
	ssize_t  ret = -1;
	u16   address;
	u8   value[4];


	struct ov5640_device *this = file->private_data;

	if ((NULL == buf) || (count < 2))
		return -1;

	//printk("%s(),%d ...\n",  __func__, __LINE__);
	ret = raw_copy_from_user(&address, buf, 2);
	if (ret != 0)
	{
		printk("%s(),%d err\n", __func__, __LINE__);
		return -1;
	}
	ret = reg_read(this, address, value);
	if (ret < 0)
	{
		printk("%s(),%d err\n", __func__, __LINE__);
		return -1;
	}

	ret = raw_copy_to_user(buf, value, 2);
	if (ret)
	{
		printk("%s(),%d err\n",	__func__, __LINE__);
		return -1;
	}

	return 2;
}


static ssize_t camera_write(struct file *file, const char __user *buf, size_t count,
                            loff_t *offset)
{
	ssize_t  ret = -1;
	u8   rx_buf[4];
	u16  address;
	u16  value;
	struct ov5640_device *this = file->private_data;

	if ((NULL == buf) || (count < 4))
		return -1;

	//printk("%s(),%d ...\n",  __func__, __LINE__);
	ret = raw_copy_from_user(rx_buf, buf, 4);
	if (ret != 0)
		return	-1;

	address = (u16)(rx_buf[1] << 8) + rx_buf[0];
	value   = (u16)(rx_buf[3] << 8) + rx_buf[2];
	ret = reg_write(this, address, value);
	if (ret < 0)
	{
		printk("%s(),%d  err\n",  __func__, __LINE__);
		return -1;
	}

	return ret;
}


static int camera_open(struct inode *inode, struct file *file)
{
	struct ov5640_device *this;

	//printk("%s() ok\n", __func__);
	this = container_of(inode->i_cdev, struct ov5640_device, cdev);
	file->private_data = this;

	this->used = 1;
	return 0;
}


static int camera_release(struct inode *inode, struct file *file)
{
	struct ov5640_device *this;

	this = container_of(inode->i_cdev, struct ov5640_device, cdev);

	this->used = 0;
	return 0;
}

struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open  			= camera_open,
	.read			= camera_read,
	.write			= camera_write,
	.release 		= camera_release,
};
#endif


#if 1
static const struct of_device_id  camera_of_match[] =
{
	{ .compatible = "jimu,camera", },
	{ /* NULL */ },
};
MODULE_DEVICE_TABLE(of, camera_of_match);


static int camera_probe(struct platform_device *pdev)
{
#if 1
	int ret = 0;
	struct device	   	*dev = &pdev->dev;
	struct device_node 	*np  =  pdev->dev.of_node;

	dev_info(dev, "%s() ...\n", __func__);

	//1. 分配内存
	struct ov5640_device *this = devm_kzalloc(dev, sizeof(*this), GFP_KERNEL);
	if (!this)
	{
		dev_err(dev, "%s(),%d err\n",  __func__, __LINE__);
		return -ENOMEM;
	}
	this->dev  		= &(pdev->dev);
	this->name 		= DRIVER_NAME;
	this->path 		= DRIVER_NAME;
	this->used = 0;

	//2. 映射寄存器
	this->reg  = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	this->base = devm_ioremap_resource(dev, this->reg);
	if (IS_ERR(this->in_base))
	{
		dev_err(dev, "%s(),%d err\n",  __func__, __LINE__);
		return -ENOMEM;
	}
	this->in_base	=  this->base +  0x10*4;
	this->out_base	=  this->base +  0x11*4;

	//	this->out_reg = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	//	this->out_base = devm_ioremap_resource(dev, this->out_reg);
	//	if (IS_ERR(this->out_base))
	//	{
	//		dev_err(dev, "%s(),%d err\n",  __func__, __LINE__);
	//		return -ENOMEM;
	//	}

	ret = of_property_read_string(np, "path", (const char **)&(this->path));
	if (ret)
	{
		dev_err(this->dev,"not find 'path' in device tree \n");
	}
	platform_set_drvdata(pdev, this);

	//3. 注册设备驱动
	//int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
	ret = alloc_chrdev_region(&(this->devno), 0, 1, this->name);
	if (ret < 0)
	{
		dev_err(dev, "alloc_chrdev_region(),%d err\n",  __LINE__);
		goto failed5;
	}
	// dev_info(dev,  "MAJOR(%d),Minor(%d) \n", MAJOR(devt), MINOR(devt));
	cdev_init(&this->cdev, &fops);
	this->cdev.owner = THIS_MODULE;
	ret = cdev_add(&this->cdev, this->devno, 1);
	if (ret)
	{
		dev_err(dev, "cdev_add(),%d err\n",  __LINE__);
		goto failed6;
	}

	//4. 建立设备节点名称
	this->class = class_create(THIS_MODULE, CLASS_NAME);
	if (IS_ERR(this->class))
	{
		dev_err(dev, "class_create(),%d err\n",  __LINE__);
		goto failed7;
	}
	//struct device *device_create(struct class *class, struct device *parent,
	//                              dev_t devt, void *drvdata,
	//								const char *fmt, ...)
	dev = device_create(this->class, NULL, this->devno, NULL,
	                    "%s", this->path);
	if (IS_ERR(dev))
	{
		dev_err(this->dev, "device_create(),%d err\n",  __LINE__);
		goto failed8;
	}
#endif

	dev_info(dev, "/dev/%s create ok\n", this->name);
	return 0;


	//failed9:
	//	device_destroy(this->class, this->devno);
failed8:
	class_destroy(this->class);
failed7:
	cdev_del(&this->cdev);
failed6:
	unregister_chrdev_region(this->devno, 1);
failed5:

	return -1;
}


static int camera_remove(struct platform_device *pdev)
{
	struct ov5640_device  *this;

	this = platform_get_drvdata(pdev);
	if (!this)
	{
		dev_err(&pdev->dev, "platform_get_drvdata(),%d err\n",  __LINE__);
		return -ENODEV;
	}

	device_destroy(this->class, this->devno);
	class_destroy(this->class);
	cdev_del(&this->cdev);
	unregister_chrdev_region(this->devno, 1);

	dev_info(&pdev->dev, "%s(),%d ok\n", __func__, __LINE__);
	return 0;
}

static struct platform_driver 	camera_driver =
{
	.probe  = camera_probe,
	.remove = camera_remove,
	.driver = {
		.name  = MODULE_NAME,
		.owner = THIS_MODULE,
		.of_match_table = camera_of_match,
	},
};

module_platform_driver(camera_driver);
#endif



MODULE_DESCRIPTION("Camera driver for ar0132");
MODULE_AUTHOR("jimu.ltd");
MODULE_LICENSE("GPL v2");




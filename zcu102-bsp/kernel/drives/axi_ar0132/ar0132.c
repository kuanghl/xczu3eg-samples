/***********************************************************************************************//**
*\n  @file       ar0132.c
*\n  @brief      ar0132 ����
*\n  @details
*\n -----------------------------------------------------------------------------------
*\n  �ļ�˵����
*\n       1. ar0132 ����
*\n       2. PLʹ��2��EMIO����ΪSCL/SDA; ���ͨ��AXI�ӿ�ֱ�ӿ��ƣ�ģ��i2c�ӿڡ�
*\n		  3. ��ַ16bit�� ����16bit,
*\n       
*\n -----------------------------------------------------------------------------------
*\n  �汾:  	 �޸���:       �޸�����:        	����:
*\n  V0.1    ������        2019.7.1        ����
*\n 
***************************************************************************************************/

/**************************************************************************************************
* ͷ�ļ�
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
* �궨�塢�ṹ����
***************************************************************************************************/
// �豸��
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

#define DEVICE_ID  (0x10 << 1)  // bit0ΪR/W


/**************************************************************************************************
* ȫ�ֱ�������������
***************************************************************************************************/


/**************************************************************************************************
* ˽�б�������������
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

	struct resource *reg;      // �Ĵ���
	void __iomem 	*base;     // ����ַ
	void __iomem 	*in_base;  // ��ȡ
	void __iomem 	*out_base; // д��

} ov5640_device;


/**************************************************************************************************
* ˽�к�������������
***************************************************************************************************/


/**************************************************************************************************
* ȫ�ֺ�������������
***************************************************************************************************/





#if 1

#define read_reg(offset)		 readl(offset)
#define write_reg(offset, val)	 writel(val, offset)



#if 3


// SCL�����ѹ
#define  SCL_OUT(val) \
	do{ \
		value  = read_reg(this->out_base);   	\
		value  = value & (~SCL_T)  & (~SCL_O); 	\
		value |= val ? SCL_O : 0;             \
		write_reg(this->out_base, value);     \
	} while(0)

// SDA�����ѹ
#define  SDA_OUT(val) \
	do{ \
		value  = read_reg(this->out_base);    \
		value  = value & (~SDA_T)  & (~SDA_O);\
		value |= val ? SDA_O : 0;             \
		write_reg(this->out_base, value);     \
	} while(0)

// ��ȡSDA��ѹ
static inline u32 SDA_IN(struct ov5640_device *this)
{
	u32 value;

	value  = read_reg(this->in_base);
	value &= SDA_I;

	return value ? 1 : 0;
}

//����SDAΪ���
#define  SET_SDA_OUT() \
	do{ \
		value  = read_reg(this->out_base);    \
		value &= ~SDA_T;                      \
		write_reg(this->out_base, value);     \
	} while(0)

// ����SDAΪ����
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

	SDA_OUT(1);     //�����߸ߵ�ƽ
	SCL_OUT(1);	    //��ʱ���߸ߵ�ʱ���������ɸ�����
	i2c_delay();
	SDA_OUT(0);
	i2c_delay();
	SCL_OUT(0);	    //�����߻ָ��͵�ƽ��������������Ҫ
}

//SCCBֹͣ�ź�
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

//i2c,д��һ���ֽ�
//����ֵ:0,�ɹ�;-1,ʧ��.
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
	SET_SDA_IN();		    // ����SDAΪ����
	i2c_delay();
	SCL_OUT(1);			// ���յھ�λ,���ж��Ƿ��ͳɹ�
	i2c_delay();
	if (SDA_IN(this))
		res = -1;  		//SDA=1����ʧ�ܣ�����-1
	else
		res =  0;  		//SDA=0���ͳɹ�������0
	SCL_OUT(0);
	SET_SDA_OUT();		//����SDAΪ���

	return res;
}

//i2c ��ȡһ���ֽ�
//��SCL��������,��������
//����ֵ:����������
u8 i2c_read_byte(struct ov5640_device *this)
{
	u32 value;

	u8 temp=0,j;
	SET_SDA_IN();		//����SDAΪ����
	for (j=8; j>0; j--) 	//ѭ��8�ν�������
	{
		i2c_delay();
		SCL_OUT(1);
		temp=temp<<1;
		if (SDA_IN(this)) temp++;
		i2c_delay();
		SCL_OUT(0);
	}
	SET_SDA_OUT();		//����SDAΪ���
	return temp;
}
#endif



// ���Ĵ���,��ȡ2bytes������(�͵�ַ��Ÿ��ֽ�)
static int reg_read(struct ov5640_device *this, u16 reg, u8 *val)
{
	int ret = 2;
	u8 value;

	
	// д��ַ
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID)) 		ret = -1;
	if (i2c_write_byte(this, reg>>8))			ret = -1;
	if (i2c_write_byte(this, reg))				ret = -1;
	i2c_stop(this);

	// ��ȡ��1���ֽ�(���ֽ�)
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID | 0X01)) ret = -1;
	value = i2c_read_byte(this);
	i2c_no_ack(this);
	i2c_stop(this);
	*(val+1) = value;

	// ��ȡ��2���ֽڣ����ֽڣ�
	i2c_start(this);
	if (i2c_write_byte(this, DEVICE_ID | 0X01)) ret = -1;
	value = i2c_read_byte(this);
	i2c_no_ack(this);
	i2c_stop(this);
	*(val) = value;

	return ret;  // ����2�ֽ�
}

// д�Ĵ���,д2bytes������(�͵�ַ��Ÿ��ֽ�)
static int reg_write(struct ov5640_device *this, u16 address, u16 data)
{
	u32 value;

	int ret = 2;

	i2c_start(this); 								//����SCCB����
	if (i2c_write_byte(this, DEVICE_ID)) 		ret =-1;	//д����ID
	if (i2c_write_byte(this, address>>8))	  	ret =-1;	//д�Ĵ�����8λ��ַ
	if (i2c_write_byte(this, address))			ret =-1;	//д�Ĵ�����8λ��ַ
	
	//д����
	if (i2c_write_byte(this, (u8)(data>>8)))	ret =-1; 	// ���ֽ�
	if (i2c_write_byte(this, (u8)data))			ret =-1;    // ���ֽ�
	i2c_stop(this);

	return	ret;  // д��2bytes
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

	//1. �����ڴ�
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

	//2. ӳ��Ĵ���
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

	//3. ע���豸����
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

	//4. �����豸�ڵ�����
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




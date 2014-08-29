/**********************************************************************
*@Filename          optical.c
*@Author            erguangs
*@Des
*@History
*                Original version, 29-Aug, 2014 
**********************************************************************/
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/ioctl.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/wait.h>
#include <linux/cdev.h>

#include <linux/interrupt.h>
#include <asm/signal.h>
#include <linux/gpio.h>
#include <linux/irq.h>
#include <linux/semaphore.h>


MODULE_AUTHOR("seg");
MODULE_DESCRIPTION("Optical driver of Smart car");
MODULE_VERSION("V1.0");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "optical"
#define OPTICAL_PHY_ADDR 0x41210000
#define INTERRUPT_ID 90
#define IRQ_MASK 0x1
#define IRQ_DEVICE_ID 0

#define NO1_MASK 1 << 0
#define NO2_MASK 1 << 1
#define NO3_MASK 1 << 2
#define NO4_MASK 1 << 3
#define NO5_MASK 1 << 4


#define OPTICAL_FULL_READ	1
#define OPTICAL_1_READ	3
#define OPTICAL_2_READ	4
#define OPTICAL_3_READ	5
#define OPTICAL_4_READ	6
#define OPTICAL_5_READ	7


static int optical_major = 0;
static unsigned long base_addr = 0;
static struct class* optical_class = NULL;
static struct device* optical_device = NULL;

static ssize_t optical_open(struct inode *inode, struct file *file)
{
	printk("open success\n");
	return 0;
}

static ssize_t optical_release(struct inode *inode, struct file *file)
{
	return 0;
}

ssize_t optical_read(struct file *filp, char __user *buf, size_t count)
{
	int val,ret;
	val = inb(base_addr);
	ret = __put_user(val,buf);
	return ret;
}

//static ssize_t optical_ioctl(struct inode *inode, struct file *file, 
//arg is a baseaddress of a long array which contains three elements.
static ssize_t optical_ioctl(struct file *file, 
								unsigned int cmd,
								unsigned long arg)
{
	u32 status = 0;
	int ret = 0;
	printk("debug:in ioctl!\n");
	switch(cmd)
	{
	case OPTICAL_FULL_READ:
		status = ioread32(base_addr);
		ret = __put_user(status, (u32 *)arg);
		printk("optical data = 0x%x\n",status);
		break;
	case OPTICAL_1_READ:
		status = ioread32(base_addr);
		if(status & NO1_MASK) 
			ret = __put_user(1, (u32 *)arg);
		else
			ret = __put_user(0, (u32 *)arg);
		break;
	case OPTICAL_2_READ:
		status = ioread32(base_addr);
		if(status & NO2_MASK) 
			ret = __put_user(1, (u32 *)arg);
		else
			ret = __put_user(0, (u32 *)arg);
		break;
	case OPTICAL_3_READ:
		status = ioread32(base_addr);
		if(status & NO3_MASK) 
			ret = __put_user(1, (u32 *)arg);
		else
			ret = __put_user(0, (u32 *)arg);
		break;
	case OPTICAL_4_READ:
		status = ioread32(base_addr);
		if(status & NO4_MASK) 
			ret = __put_user(1, (u32 *)arg);
		else
			ret = __put_user(0, (u32 *)arg);
		break;
	case OPTICAL_5_READ:
		status = ioread32(base_addr);
		if(status & NO5_MASK) 
			ret = __put_user(1, (u32 *)arg);
		else
			ret = __put_user(0, (u32 *)arg);
		break;
	default:
		printk("cmd=%d\n",cmd);
		break;
	}
	return 0;
}

static struct file_operations optical_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = optical_ioctl,
	.open = optical_open,
	.release = optical_release,
	.read = optical_read,
};

static int __init optical_init(void) 
{
	int ret;
	ret = register_chrdev(0,DEVICE_NAME, &optical_fops);
	if(ret < 0)
	{
		printk("optical: can't get major number\n");
		return ret;
	}
	optical_major = ret;
	optical_class = class_create(THIS_MODULE, "optical_class");
	if(IS_ERR(optical_class))
	{
		printk("optical: failed in creating class\n");
		unregister_chrdev(optical_major, DEVICE_NAME);
		return -1;
	}
	optical_device = device_create(optical_class,\
									  NULL, \
									  MKDEV(optical_major, 0), \
									  NULL,\
									  DEVICE_NAME);
	if(IS_ERR(optical_device))
	{
		printk("optical: failed in creating device!\n");
		unregister_chrdev(optical_major, DEVICE_NAME);
		class_unregister(optical_class);
		class_destroy(optical_class);
		return -1;
	}
	base_addr = (unsigned long) ioremap(OPTICAL_PHY_ADDR, sizeof(u32));
	printk("Optical initial successfully\n");
	return 0;
}
static void __exit optical_exit(void)
{
  device_destroy(optical_class, MKDEV(optical_major, 0));
  class_unregister(optical_class);
  class_destroy(optical_class);
  unregister_chrdev(optical_major, DEVICE_NAME);
  printk("optical module exit.\n");
}
module_init(optical_init);
module_exit(optical_exit);

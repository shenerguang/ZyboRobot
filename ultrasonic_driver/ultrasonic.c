/**********************************************************************
*@Filename          ultrasonic.c
*@Author            erguangs
*@Des
*@History
*                Original version, 16-Jul, 2013 zulongp
*                modify for zrobot IV,  29-Aug, 2014 
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


MODULE_AUTHOR("seg");
MODULE_DESCRIPTION("Ultrasonic driver of Smart car");
MODULE_VERSION("V1.0");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "ultrasonic"
#define ULTRASONIC_PHY_ADDR 0x43C10000
#define INTERRUPT_ID 91

#define ULTRASONIC_STATUS_OFFSET 0
#define ULTRASONIC_ECHO1_OFFSET  0x04
#define ULTRASONIC_ECHO2_OFFSET  0x08
#define ULTRASONIC_ECHO3_OFFSET  0x0C

#define ULTRASONIC_IOC_MAGIC    'Z' 

#define ULTRASONIC_ECHO_READ   _IOR(ULTRASONIC_IOC_MAGIC, 1, int)

#define ULTRASONIC_IOC_MAXNR     10

static int ultrasonic_major = 0;
static unsigned long base_addr = 0;
static struct class* ultrasonic_class = NULL;
static struct device* ultrasonic_device = NULL;

static ssize_t ultrasonic_open(struct inode *inode, struct file *file)
{
	printk("open success\n");
	return 0;
}

static ssize_t ultrasonic_release(struct inode *inode, struct file *file)
{
	return 0;
}

//static ssize_t ultrasonic_ioctl(struct inode *inode, struct file *file, 
//arg is a baseaddress of a long array which contains three elements.
static ssize_t ultrasonic_ioctl(struct file *file, 
								unsigned int cmd,
								unsigned long arg)
{
	u32 status[3] = {0};
	u32 data = 0;
	int err = 0,ret = 0;
	if(_IOC_TYPE(cmd) != ULTRASONIC_IOC_MAGIC)return -ENOTTY;
	if(_IOC_NR(cmd) > ULTRASONIC_IOC_MAXNR) return -ENOTTY;

	if(_IOC_DIR(cmd) &_IOC_READ)
		err = !access_ok(VERIFY_WRITE,(void __user*)arg, _IOC_SIZE(cmd));
	else if(_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_READ, (void __user *)arg,_IOC_SIZE(cmd));
	if(err) return -EFAULT;
	switch(cmd)
	{
	case ULTRASONIC_ECHO_READ:
		iowrite32(0x1,base_addr + ULTRASONIC_STATUS_OFFSET);
		data = ioread32(base_addr + ULTRASONIC_STATUS_OFFSET);
		while(!(data & (1 << 1)) || !(data & (1 << 2)) || !(data & (1 << 3)))
			data = ioread32(base_addr + ULTRASONIC_STATUS_OFFSET);
		status[0] = ioread32(base_addr + ULTRASONIC_ECHO1_OFFSET);
		status[1] = ioread32(base_addr + ULTRASONIC_ECHO2_OFFSET);
		status[2] = ioread32(base_addr + ULTRASONIC_ECHO3_OFFSET);
		ret = __put_user(status[0], (u32 *)arg);
		ret = __put_user(status[1], (u32 *)arg+1);
		ret = __put_user(status[2], (u32 *)arg+2);
		printk("echo1 data = 0x%x\n",status[0]);
		printk("echo2 data = 0x%x\n",status[1]);
		printk("echo3 data = 0x%x\n",status[2]);
		break;
	default:
		break;
	}
	return 0;
}
static struct file_operations ultrasonic_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = ultrasonic_ioctl,
	.open = ultrasonic_open,
	.release = ultrasonic_release,
};
static int __init ultrasonic_init(void) 
{
	int ret;
	ret = register_chrdev(0,DEVICE_NAME, &ultrasonic_fops);
	if(ret < 0)
	{
		printk("ultrasonic: can't get major number\n");
		return ret;
	}
	ultrasonic_major = ret;
	ultrasonic_class = class_create(THIS_MODULE, "ultrasonic_class");
	if(IS_ERR(ultrasonic_class))
	{
		printk("ultrasonic: failed in creating class\n");
		unregister_chrdev(ultrasonic_major, DEVICE_NAME);
		return -1;
	}
	ultrasonic_device = device_create(ultrasonic_class,\
									  NULL, \
									  MKDEV(ultrasonic_major, 0), \
									  NULL,\
									  DEVICE_NAME);
	if(IS_ERR(ultrasonic_device))
	{
		printk("ultrasonic: failed in creating device!\n");
		unregister_chrdev(ultrasonic_major, DEVICE_NAME);
		class_unregister(ultrasonic_class);
		class_destroy(ultrasonic_class);
		return -1;
	}
	base_addr = (unsigned long) ioremap(ULTRASONIC_PHY_ADDR, sizeof(u32));
	printk("Ultrasonic initail successfully\n");
	return 0;
}
static void __exit ultrasonic_exit(void)
{
  device_destroy(ultrasonic_class, MKDEV(ultrasonic_major, 0));
  class_unregister(ultrasonic_class);
  class_destroy(ultrasonic_class);
  unregister_chrdev(ultrasonic_major, DEVICE_NAME);
  printk("ultrasonic module exit.\n");
}
module_init(ultrasonic_init);
module_exit(ultrasonic_exit);

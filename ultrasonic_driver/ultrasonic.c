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
#include <linux/semaphore.h>


MODULE_AUTHOR("seg");
MODULE_DESCRIPTION("Ultrasonic driver of Smart car");
MODULE_VERSION("V2.1");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "ultrasonic"
#define ULTRASONIC_PHY_ADDR 0x43C10000
#define INTERRUPT_ID 91
#define IRQ_MASK 0x1
#define IRQ_DEVICE_ID 0

#define ULTRASONIC_STATUS_OFFSET 0
#define ULTRASONIC_ECHO1_OFFSET  0x04
#define ULTRASONIC_ECHO2_OFFSET  0x08
#define ULTRASONIC_ECHO3_OFFSET  0x0C


#define ULTRASONIC_ECHO_READ	1

#define ULTRASONIC_IOC_MAXNR     10

static int ultrasonic_major = 0;
static unsigned long base_addr = 0;
static struct class* ultrasonic_class = NULL;
static struct device* ultrasonic_device = NULL;

typedef struct {
    dev_t dev_no;
    u32 IsReady;
    int InterruptPresent;
}ULT_DEV;

static ULT_DEV ultdev;
static struct semaphore sem;

static irqreturn_t ult_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	up(&sem);	
	printk("V\n");
}

static ssize_t ultrasonic_open(struct inode *inode, struct file *file)
{
	int ret = 0;

	sema_init(&sem,0);
	ret = request_irq(INTERRUPT_ID, ult_interrupt,IRQF_TRIGGER_RISING, DEVICE_NAME, &ultdev);
	if(ret)
    {
        printk("could not register interrupt!");
        return ret;
    }
	printk("open success\n");
	return 0;
}

static ssize_t ultrasonic_release(struct inode *inode, struct file *file)
{
	free_irq(INTERRUPT_ID,&ultdev);
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
	printk("debug:in ioctl!\n");
	switch(cmd)
	{
	case ULTRASONIC_ECHO_READ:
		printk("aaa");
		iowrite32(0x1,base_addr + ULTRASONIC_STATUS_OFFSET);
		printk("P\n");
		down(&sem);
		printk("P done\n");
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
		printk("cmd=%d\n",cmd);
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
	printk("Ultrasonic initial successfully\n");
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

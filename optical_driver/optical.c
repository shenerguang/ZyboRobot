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
#define XGPIO_GIE_OFFSET    0x11C /**< Glogal interrupt enable register */
#define XGPIO_ISR_OFFSET    0x120 /**< Interrupt status register */
#define XGPIO_IER_OFFSET    0x128 /**< Interrupt enable register */
#define XGPIO_GIE_GINTR_ENABLE_MASK 0x80000000


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
#define OPTICAL_WAIT_READ	9


static int optical_major = 0;
static unsigned long base_addr = 0;
static struct class* optical_class = NULL;
static struct device* optical_device = NULL;

typedef struct {
    dev_t dev_no;
    u32 IsReady;
    int InterruptPresent;
}OPT_DEV;

static OPT_DEV optdev;
static struct semaphore sem;
static int flag;

static void InterruptClear()
{
        u32 val;
        val = ioread32(base_addr + XGPIO_ISR_OFFSET);
        iowrite32(val & IRQ_MASK,base_addr + XGPIO_ISR_OFFSET);
        printk("int cleared");
}
static irqreturn_t opt_interrupt(int irq, void *dev_id, struct pt_regs *regs)
{
	printk("in interrupt\n");
   	up(&sem);
    printk("V\n");
	InterruptClear();
    return 0;

}
static void InterruptEnable()
{
    u32 val;
    //printk("debug1 read addr = %lx\n",key_addr+XGPIO_IER_OFFSET);
    //            0x128
    //val = ioread32(key_addr + XGPIO_IER_OFFSET);
    //printk("debug2 val=%lx\n",val);
    //                   0x128                  0x1
    iowrite32(val | IRQ_MASK,base_addr + XGPIO_IER_OFFSET);
    //printk("debug3 ");
    //           0x11c            0x80000000
    iowrite32(XGPIO_GIE_GINTR_ENABLE_MASK,base_addr + XGPIO_GIE_OFFSET);
}

static ssize_t optical_open(struct inode *inode, struct file *file)
{
	int ret;
	flag = 0;
	sema_init(&sem,0);
    ret = request_irq(INTERRUPT_ID, opt_interrupt,IRQF_TRIGGER_RISING, DEVICE_NAME, &optdev);
    if(ret)
    {
        printk("could not register interrupt!");
        return ret;
    }

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
	int *val = 0;
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
	case OPTICAL_WAIT_READ:
		status = ioread32(base_addr);
		val = (u32 *)arg;
		printk("val:%x,status:%x;eq:%d",*val,status,*val==status);
		if(*val==status) 
		{
			//enter wait status
			InterruptEnable();
			printk("P\n");
			down(&sem);
			status = ioread32(base_addr);
		}
		ret = __put_user(status, (u32 *)arg);
		printk("different optical data = 0x%x\n",status);
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

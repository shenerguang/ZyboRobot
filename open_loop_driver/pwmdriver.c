#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "pwm_device"
#define MYPWM_PHY_ADDR 0x43c01000
#define MYGPIO_PHY_ADDR 0x41200000
#define WHEEL_OFFSET 0x1000

MODULE_AUTHOR("zlpan");
MODULE_DESCRIPTION("pwm");
MODULE_VERSION("v2.0");
MODULE_LICENSE("GPL");

static int pwm_major;
static struct class* pwm_class = NULL;
static struct device* pwm_device = NULL;

unsigned long mypwm_addr = 0;
unsigned long mygpio_addr = 0;


/**
  *buf:set the value of 4 leds 
  **/
static ssize_t sys_value_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    unsigned char num = 0;
	sscanf(buf,"%x",&num);
	outb(num,mygpio_addr+8);
    return count;
}

/**
  *buf:get the value of 4 sws 
  **/
static ssize_t sys_value_get (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
	int aa;
	unsigned char num = 0;
	num = inb(mygpio_addr);
	aa = __put_user(num,buf);
    return count;
}

/**
 *set the speed of pwn+x
 *if bit[31]=0 stop
 *else go
 */
static ssize_t sys_pwm_left_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	printk("debug: at pwm left speed main!\n");
	sscanf(buf,"%d",&num);
	printk("debug: get num:%d\n",num);
	printk("debug: addr = :0x%x\n",mypwm_addr);
    iowrite32(num == 0 ? 0 : (num | 0x80000000), mypwm_addr);
    return count;
}

static ssize_t sys_pwm_left_dir_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    iowrite32(num, mypwm_addr + 4);
    return count;
}

static ssize_t sys_pwm_right_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    iowrite32(num == 0 ? 0 : (num | 0x80000000), mypwm_addr + 8);
    return count;
}

static ssize_t sys_pwm_right_dir_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    iowrite32(num, mypwm_addr + 12);
    return count;
}

//led set
static DEVICE_ATTR(value_set, S_IWUSR, NULL, sys_value_set);
//sw get
static DEVICE_ATTR(value_get, S_IWUSR, NULL, sys_value_get);
//pwm speed
static DEVICE_ATTR(pwm_left_speed, S_IWUSR, NULL, sys_pwm_left_speed_set);
static DEVICE_ATTR(pwm_right_speed, S_IWUSR, NULL, sys_pwm_right_speed_set);
//pwm direction
static DEVICE_ATTR(pwm_left_dir, S_IWUSR, NULL, sys_pwm_left_dir_set);
static DEVICE_ATTR(pwm_right_dir, S_IWUSR, NULL, sys_pwm_right_dir_set);

static ssize_t pwm_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

	//printk("fun(gpio_ioctl):");
    u32 status = 0xff;
    int ret;
	printk("debug : in ioctl!!");
    switch(cmd){
        case 0:
        case 1:
			//1. pwm left speed
    		iowrite32(arg == 0 ? 0 : (arg | 0x80000000), mypwm_addr);
			printk("left speed\n");
			return 0;
		case 5:
			//2. pwm left direction
    		iowrite32(arg, mypwm_addr + 4);
			printk("left dir\n");
			return 0;
		case 3:
			//3. pwm right speed
    		iowrite32(arg == 0 ? 0 : (arg | 0x80000000), mypwm_addr + 8);
			printk("right speed\n");
			return 0;
		case 4:
			//4. pwm right direction
    		iowrite32(arg, mypwm_addr + 12);
			printk("right dir\n");
			return 0;
		default:
			printk("default cmd=%d\n",cmd);
			return -EINVAL;
	}

}
static struct file_operations pwm_fops = {
    .owner = THIS_MODULE,
	.unlocked_ioctl = pwm_ioctl,
};

static int __init mydriver_module_init(void)
{
    int ret;

    pwm_major=register_chrdev(0, DEVICE_NAME, &pwm_fops);
    if (pwm_major < 0){
        printk("failed to register device.\n");
        return -1;
    }

    pwm_class = class_create(THIS_MODULE, "pwm_class");
    if (IS_ERR(pwm_class)){
        printk("failed to create device class.\n");
        unregister_chrdev(pwm_major, DEVICE_NAME);
        return -1;
    }


    pwm_device = device_create(pwm_class, NULL, MKDEV(pwm_major, 0), NULL, "pwm_device");
    if (IS_ERR(pwm_device)){
        printk("failed to create device .\n");
        unregister_chrdev(pwm_major, DEVICE_NAME);
        return -1;
    }

//gpio
    ret = device_create_file(pwm_device, &dev_attr_value_set);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    ret = device_create_file(pwm_device, &dev_attr_value_get);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
//pwm
    ret = device_create_file(pwm_device, &dev_attr_pwm_left_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_right_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_left_dir);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_right_dir);
    if (ret < 0)
        printk("failed to create /sys endpoint");
    
    mypwm_addr = (unsigned long)ioremap(MYPWM_PHY_ADDR, sizeof(u32));
    //mygpio_addr = (unsigned long)ioremap(MYGPIO_PHY_ADDR, sizeof(u32));
	//set the direction of sws and leds
    //outb(0xf, mygpio_addr+4);
    //outb(0x0, mygpio_addr+12);

    printk("my pwm driver initial successfully!\n");
    return 0;
}

static void __exit mydriver_module_exit(void)
{
    device_remove_file(pwm_device, &dev_attr_value_set);
    device_remove_file(pwm_device, &dev_attr_value_get);
    device_remove_file(pwm_device, &dev_attr_pwm_left_speed);
    device_remove_file(pwm_device, &dev_attr_pwm_right_speed);
    device_remove_file(pwm_device, &dev_attr_pwm_left_dir);
    device_remove_file(pwm_device, &dev_attr_pwm_right_dir);
    device_destroy(pwm_class, MKDEV(pwm_major, 0));
    class_unregister(pwm_class);
    class_destroy(pwm_class);
    unregister_chrdev(pwm_major, DEVICE_NAME);
    printk("pwm module exit.\n");
}

module_init(mydriver_module_init);
module_exit(mydriver_module_exit);

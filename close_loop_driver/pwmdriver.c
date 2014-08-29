#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "pwm_new"
#define MYPWML_PHY_ADDR 0x43C01000
#define MYPWMR_PHY_ADDR 0x43C02000

#define CTRL_OFFSET 0 
#define IN_SPEED_SET_OFFSET 1 * 4
#define IN_KP_PARAM_OFFSET 2 * 4
#define IN_KI_PARAM_OFFSET 3 * 4
#define IN_PID_OUT_MAX_OFFSET 4 * 4
#define IN_PID_OUT_MIN_OFFSET 5 * 4
#define IN_PID_UI_LIMIT_OFFSET 6 * 4

#define RESET_OFFSET 14 * 4
#define OUT_CUR_SPEED_OFFSET 15 * 4


MODULE_AUTHOR("erguangs");
MODULE_DESCRIPTION("pwm");
MODULE_VERSION("v3.0");
MODULE_LICENSE("GPL");

static int pwm_major;
static struct class* pwm_class = NULL;
static struct device* pwm_device = NULL;

unsigned long mypwml_addr = 0;
unsigned long mypwmr_addr = 0;

/**
 *set the speed of left wheel
 */
static ssize_t sys_pwm_left_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	printk("debug: at pwm left speed main!\n");
	sscanf(buf,"%d",&num);
	printk("debug: get num:%d\n",num);
    iowrite32(num , mypwml_addr + IN_SPEED_SET_OFFSET );
    return count;
}

static ssize_t sys_pwm_left_speed_read (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 status = 0;
    status = ioread32(mypwml_addr + OUT_CUR_SPEED_OFFSET);
    return status;
}

static ssize_t sys_pwm_right_speed_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
    iowrite32(num, mypwmr_addr + IN_SPEED_SET_OFFSET );
    return count;
}

static ssize_t sys_pwm_right_speed_read (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 status = 0;
    status = ioread32(mypwmr_addr + OUT_CUR_SPEED_OFFSET);
    return status;
}

static ssize_t sys_pwm_init_set (struct device* dev, struct device_attribute* attr, const char* buf, size_t count)
{
    u32 num = 0;
	sscanf(buf,"%d",&num);
	if(num == "1")
	{
		printk("init left pwm!\n");
		iowrite32(0 ,mypwml_addr + CTRL_OFFSET);
		iowrite32(-0 ,mypwml_addr + IN_SPEED_SET_OFFSET);
		iowrite32(1<<8 ,mypwml_addr + IN_KP_PARAM_OFFSET);
		iowrite32(1<<8 ,mypwml_addr + IN_KI_PARAM_OFFSET);
		iowrite32(63 ,mypwml_addr + IN_PID_OUT_MAX_OFFSET );
		iowrite32(-63 ,mypwml_addr + IN_PID_OUT_MIN_OFFSET );
		iowrite32(70<<8 ,mypwml_addr + IN_PID_UI_LIMIT_OFFSET );

		iowrite32(0 ,mypwml_addr + RESET_OFFSET );
		iowrite32(0x0ff ,mypwml_addr +  RESET_OFFSET );

		iowrite32(1 ,mypwml_addr + CTRL_OFFSET);

		printk("init right pwm!\n");
		iowrite32(0 ,mypwmr_addr + CTRL_OFFSET);
		iowrite32(-0 ,mypwmr_addr + IN_SPEED_SET_OFFSET);
		iowrite32(1<<8 ,mypwmr_addr + IN_KP_PARAM_OFFSET);
		iowrite32(1<<8 ,mypwmr_addr + IN_KI_PARAM_OFFSET);
		iowrite32(63 ,mypwmr_addr + IN_PID_OUT_MAX_OFFSET );
		iowrite32(-63 ,mypwmr_addr + IN_PID_OUT_MIN_OFFSET );
		iowrite32(70<<8 ,mypwmr_addr + IN_PID_UI_LIMIT_OFFSET );

		iowrite32(0 ,mypwmr_addr + RESET_OFFSET );
		iowrite32(0x0ff ,mypwmr_addr + RESET_OFFSET );

		iowrite32(1 ,mypwmr_addr + CTRL_OFFSET);
		printk("init finished!\n");
	}
    return count;
}

//pwm speed
static DEVICE_ATTR(pwm_left_speed, S_IWUSR, NULL, sys_pwm_left_speed_set);
static DEVICE_ATTR(pwm_right_speed, S_IWUSR, NULL, sys_pwm_right_speed_set);
static DEVICE_ATTR(pwm_init, S_IWUSR, NULL, sys_pwm_init_set);
static DEVICE_ATTR(pwm_left_read, S_IWUSR, NULL, sys_pwm_left_speed_read);
static DEVICE_ATTR(pwm_right_read, S_IWUSR, NULL, sys_pwm_right_speed_read);

static ssize_t pwm_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{

    u32 status = 0xff;
    int ret;
	printk("debug : in ioctl!!");
    switch(cmd){
        case 0:
        case 1:
			//1. pwm init
			printk("no init");
			return 0;
		case 3:
			//2. pwm left speed set 
			printk("arg=%d\n",arg);
    		iowrite32(arg, mypwml_addr + IN_SPEED_SET_OFFSET );
			printk("left speed set\n");
			status = ioread32(mypwml_addr); 
			printk("ctl = 0x%x\n",status);
			status = ioread32(mypwml_addr + RESET_OFFSET ); 
			printk("rst = 0x%x\n",status);
			return 0;
		case 4:
			//2. pwm left speed read
			// the input number should be a pointer
			status = ioread32(mypwml_addr+OUT_CUR_SPEED_OFFSET );
			ret = __put_user(status, (long *)arg); 
			return 0;
		case 5:
			//3. pwm right speed
			printk("arg=%d\n",arg);
    		iowrite32(arg, mypwmr_addr + IN_SPEED_SET_OFFSET );
			printk("right speed set\n");
			return 0;
		case 6:
			//3. pwm right speed read
			// the input number should be a pointer
			status = ioread32(mypwmr_addr+OUT_CUR_SPEED_OFFSET );
			ret = __put_user(status, (long *)arg); 
			return 0;
		default:
			printk("default cmd=%d\n",cmd);
			return -EINVAL;
	}

}

int pwm_open(struct inode *inode, struct file *filp)
{
    printk("pwm open and init\n");
		printk("init left pwm!\n");

		printk("left addr = %x\n",mypwml_addr );
		printk("right addr = %x\n",mypwmr_addr );
		iowrite32(0 ,mypwml_addr + CTRL_OFFSET);
		iowrite32(-0 ,mypwml_addr + IN_SPEED_SET_OFFSET);
		iowrite32(1<<8 ,mypwml_addr + IN_KP_PARAM_OFFSET);
		iowrite32(1<<8 ,mypwml_addr + IN_KI_PARAM_OFFSET);
		iowrite32(63 ,mypwml_addr + IN_PID_OUT_MAX_OFFSET );
		iowrite32(-63 ,mypwml_addr + IN_PID_OUT_MIN_OFFSET );
		iowrite32(70<<8 ,mypwml_addr + IN_PID_UI_LIMIT_OFFSET );

		iowrite32(0 ,mypwml_addr + RESET_OFFSET );
		iowrite32(0x0ff ,mypwml_addr + RESET_OFFSET );

		iowrite32(1 ,mypwml_addr + CTRL_OFFSET);

		printk("init right pwm!\n");
		iowrite32(0 ,mypwmr_addr + CTRL_OFFSET);
		iowrite32(-0 ,mypwmr_addr + IN_SPEED_SET_OFFSET);
		iowrite32(1<<8 ,mypwmr_addr + IN_KP_PARAM_OFFSET);
		iowrite32(1<<8 ,mypwmr_addr + IN_KI_PARAM_OFFSET);
		iowrite32(63 ,mypwmr_addr + IN_PID_OUT_MAX_OFFSET );
		iowrite32(-63 ,mypwmr_addr + IN_PID_OUT_MIN_OFFSET );
		iowrite32(70<<8 ,mypwmr_addr + IN_PID_UI_LIMIT_OFFSET );

		iowrite32(0 ,mypwmr_addr + RESET_OFFSET );
		iowrite32(0x0ff ,mypwmr_addr + RESET_OFFSET );

		iowrite32(1 ,mypwmr_addr + CTRL_OFFSET);
		printk("init finished!\n");
		printk("you can now control weels!\n");
	
    return 0;
}

static struct file_operations pwm_fops = {
    .owner = THIS_MODULE,
	.unlocked_ioctl = pwm_ioctl,
	.open = pwm_open,
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

//pwm attr create and can be control through shell
    ret = device_create_file(pwm_device, &dev_attr_pwm_left_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_right_speed);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_init);
    if (ret < 0)
        printk("failed to create /sys endpoint");


    ret = device_create_file(pwm_device, &dev_attr_pwm_right_read);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    ret = device_create_file(pwm_device, &dev_attr_pwm_left_read);
    if (ret < 0)
        printk("failed to create /sys endpoint");

    mypwml_addr = (unsigned long)ioremap(MYPWML_PHY_ADDR, 16);
    mypwmr_addr = (unsigned long)ioremap(MYPWMR_PHY_ADDR, 16);

    printk("my pwm driver initial successfully!\n");
    return 0;
}

static void __exit mydriver_module_exit(void)
{
    device_remove_file(pwm_device, &dev_attr_pwm_left_speed);
    device_remove_file(pwm_device, &dev_attr_pwm_right_speed);
    device_remove_file(pwm_device, &dev_attr_pwm_init);
    device_destroy(pwm_class, MKDEV(pwm_major, 0));
    class_unregister(pwm_class);
    class_destroy(pwm_class);
    unregister_chrdev(pwm_major, DEVICE_NAME);
    printk("pwm module exit.\n");
}

module_init(mydriver_module_init);
module_exit(mydriver_module_exit);

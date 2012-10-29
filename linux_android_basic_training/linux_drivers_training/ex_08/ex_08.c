/*
 * file name: ex_08.c
 * purpose: Create a module to get the value of gpio after insert it
 * creator: Allan xing
 * create time: 2012-10-23
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/memory.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <mach/mfp-mmp2.h>

#define DEV_NAME 	"gpio_test"
#define MAJOR_NUM 	0
#define MINOR_NUM 	0

//make device structure
struct global_dev
{
	struct cdev test_cdev;
};
struct global_dev gdev;
struct class *driver_class;
dev_t devno;

static const struct file_operations test_fops = {
	.owner		= THIS_MODULE
};

static void global_setup_cdev(struct global_dev dev,int index)
{
	int ret = 0;
	//2 register device
	//initialize device
	cdev_init(&gdev.test_cdev,&test_fops);
	//add cdev to kernel
	ret = cdev_add(&gdev.test_cdev,devno,1);
	if(ret<0)
	{
		printk("add  error!\n");
		goto err1;
	}
err1:
	unregister_chrdev_region(devno,1);//if registration failed,unregister it
}
static int __init char_init(void)
{
	int ret=0;
	int gpio_value = 0;
	int cam_enable = mfp_to_gpio(GPIO68_GPIO);
	//1 register device
	if(MAJOR_NUM)
	{
		devno = MKDEV(MAJOR_NUM,MINOR_NUM);
		ret = register_chrdev_region(devno,1,DEV_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&devno,MINOR_NUM,1,DEV_NAME);
	}
	if(ret<0)
	{
		printk("register error!\n");
		goto err0;
	}
	global_setup_cdev(gdev,0);

	gpio_value = gpio_get_value(cam_enable);//get the value of GPIO
	printk("gpio68: %d\n",gpio_value);

	//Creating a device node
	driver_class = class_create(THIS_MODULE,DEV_NAME);
	device_create(driver_class,NULL,devno,NULL,DEV_NAME);
	printk("major=%d,minor=%d\n",MAJOR(devno),MINOR(devno));
	printk("Hello kernel!\n");
	return 0;
err0:
	unregister_chrdev_region(devno,1);//if registration failed,unregister it
	return ret;
}

static void __exit char_exit(void)
{
	//1 delete the cdev from kernel
	cdev_del(&gdev.test_cdev);
	//2 Cancellation of the device number
	unregister_chrdev_region(devno,1);

	printk("Good bye kernel!\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan");




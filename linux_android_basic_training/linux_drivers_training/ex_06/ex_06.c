/*
 * file name: ex_06.c
 * purpose: a timer module
 * creator: Allan xing
 * create time: 2012-10-10
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/memory.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/semaphore.h> 
#include <linux/timer.h>
#include <asm/uaccess.h>

#define MAJOR_NUM  	0
#define MINOR_NUM  	0
#define DEV_NAME	"timer"
#define delay		5*HZ

struct global_dev
{
	struct cdev 		test_cdev;
	atomic_t 			counter;//Atomic variables
	struct timer_list 	my_timer;
};
struct global_dev gdev;
struct global_dev *global_devp;
struct class *driver_class;
dev_t devno;

static void my_timer_handle(unsigned long data)
{
	printk("time out![%d],current process[%s]\n",(int)data,current->comm);
	mod_timer(&global_devp->my_timer,jiffies + HZ);//Be called each second
	atomic_inc(&global_devp->counter);

	printk("current jiffies is %ld\n",jiffies);
}

static int char_open(struct inode *node, struct file *file)
{
	file->private_data = global_devp;

	//init timer
	init_timer(&global_devp->my_timer);

	global_devp->my_timer.function = &my_timer_handle;
	global_devp->my_timer.expires = jiffies + delay;//delay for 5 seconds
	global_devp->my_timer.data = (unsigned long)88;
	//add timer
	add_timer(&global_devp->my_timer);

	atomic_set(&global_devp->counter,0);
	printk("open device!\n");
	return 0;
}
static int char_close(struct inode *node, struct file *file)
{
	struct global_dev *dev=file->private_data;
	del_timer(&dev->my_timer);
	printk("close device!\n");
	return 0;
}

static ssize_t char_read(struct file *file,char __user* buffer,size_t size,loff_t *offset)
{
	struct global_dev *dev = file->private_data;
	int counter;

	counter = atomic_read(&dev->counter);
	if(put_user(counter,(int*)buffer))
		return -EFAULT;
	else
		return sizeof(unsigned int);
}

static const struct file_operations test_fops = {
	.open		= char_open,
	.release	= char_close,
	.read		= char_read,
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
	global_devp = kmalloc(sizeof(struct global_dev),GFP_KERNEL);
	if(!global_devp)
	{
		ret = -EINVAL;
		goto err0;
	}
	global_setup_cdev(gdev,0);
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




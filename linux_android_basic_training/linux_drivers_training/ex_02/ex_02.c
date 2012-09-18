/*
 * file name: ex_02.c
 * purpose: a simple driver of char
 * creator: Allan xing
 * create time: 2012-09-17
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/cdev.h>

unsigned int major = 0;
unsigned int minor = 0;
dev_t devno;

struct cdev test_cdev;

static int char_open(struct inode *node, struct file *file)
{
	printk("open device!\n");
	return 0;
}
static int char_close(struct inode *node, struct file *file)
{
	printk("close device!\n");
	return 0;
}

static ssize_t char_read(struct file *file,char __user* buffer,size_t count,loff_t *offset)
{
	return 0;
}
static ssize_t char_write(struct file *file, const char __user *buffer, size_t count, loff_t *offset)
{
	return 0;
}
static long char_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
	return 0;
}

static const struct file_operations test_fops = {
	.open		= char_open,
	.release	= char_close,
	.read		= char_read,
	.write		= char_write,
	.compat_ioctl		=char_ioctl,
	.owner		= THIS_MODULE
};

static int __init char_init(void)
{
	int ret=0;
	//1 register device
	if(major){
		devno = MKDEV(major,minor);
		ret = register_chrdev_region(devno,1,"chardev");
	}else{
		ret = alloc_chrdev_region(&devno,minor,1,"chardev");
		major = MAJOR(devno);
		minor = MINOR(devno);
	}
	if(ret<0){
		printk("register error!\n");
		goto err0;
	}
	printk("major=%d,minor=%d\n",major,minor);
	//2 register device
	//initialize device
	cdev_init(&test_cdev,&test_fops);
	//add cdev to kernel
	ret = cdev_add(&test_cdev,devno,1);
	if(ret<0){
		printk("add  error!\n");
		goto err1;
	}

	printk("Hello kernel\n");
	return 0;

err1:
	unregister_chrdev_region(devno,1);//if Registration failed,unregister it
err0:
	return ret;
}

static void __exit char_exit(void)
{
	//1 delete the cdev from kernel
	cdev_del(&test_cdev);
	//2 Cancellation of the device number
	unregister_chrdev_region(devno,1);

	printk("Good bye kernel\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan");

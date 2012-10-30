/*
 * file name: gpio_misc_test.c
 * dscription: create a misc device to test gpio value
 * creator: Allan xing
 * create time: 2012-10-30
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/memory.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <asm/system.h>
#include <linux/uaccess.h>
#include <mach/mfp-mmp2.h>//gpio

#define DEV_NAME "misc_device"
#define MEM_SIZE  0x1000

struct global_dev
{
	struct cdev cdev;
	char memory[MEM_SIZE];
};
struct global_dev *gdev;
dev_t devno;

static int misc_open(struct inode *node,struct file *filp)
{
	filp->private_data = gdev;
	printk("Open device!\n");
	return 0;
}

static int misc_close(struct inode *node,struct file *filp)
{
	printk("Close device!\n");
	return 0;
}

static ssize_t misc_write(struct file *filp,const char __user *buffer,size_t size,loff_t *offset)
{
	int ret=0;
	unsigned long p=*offset;
	unsigned int count=size;
	int gpio_value = 0;
	int cam_enable = mfp_to_gpio(GPIO68_GPIO);

	struct global_dev *dev = filp->private_data;

	if(count < 0 || count > MEM_SIZE)
	{
		ret = -EINVAL;
	}
	if(count > MEM_SIZE - p)
	{
		count = MEM_SIZE - p;
	}
	ret=copy_from_user(&dev->memory + p,buffer,count);
	if(ret != 0)
	{
		*offset += count;
		ret = count;
		printk("Write %u bytes from %lu\n",count,p);
		gpio_value = gpio_get_value(cam_enable);
		printk("gpio68: %d\n",gpio_value);
	}
	return ret;
}

static ssize_t misc_read(struct file *filp,char __user *buffer,size_t size,loff_t *offset)
{
	int ret=0;
	unsigned long p=*offset;
	unsigned int count=size;

	struct global_dev *dev = filp->private_data;

	if(count < 0 || count > MEM_SIZE)
	{
		ret = -EINVAL;
	}
	if(count > MEM_SIZE - p)
		count = MEM_SIZE - p;
	if(copy_to_user(buffer,&dev->memory + p,count))
		ret = -EINVAL;
	else
	{
		*offset += count;
		ret = count;
		printk("Read %u bytes from %lu\n",count,p);
	}
	return ret;
}

static const struct file_operations fops={
	.open		= misc_open,
	.release	= misc_close,
	.read		= misc_read,
	.write		= misc_write,
	.owner		= THIS_MODULE
};
//Misc device operational structure 
static struct miscdevice misc={
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= DEV_NAME,
	.fops	= &fops
};

static int __init misc_init(void)
{
	int ret=0;
	gdev=kmalloc(sizeof(struct global_dev),GFP_KERNEL);
	if(!gdev)
	{
		ret = -ENOMEM;
	}
	memset(gdev,0,sizeof(struct global_dev));
	//register misc device
	ret = misc_register(&misc);
	printk(DEV_NAME"initialized!\n");
	return ret;
}

static void __exit misc_exit(void)
{
	kfree(gdev);
	//unregister misc device
	misc_deregister(&misc);
	printk("Goodbye kernel!");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan xing");

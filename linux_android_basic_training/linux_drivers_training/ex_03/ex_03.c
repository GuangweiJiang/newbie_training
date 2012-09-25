/*
 * file name: ex_03.c
 * dscription: a driver fo misc
 * creator: Allan xing
 * create time: 2012-09-24
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
#include <asm/uaccess.h>

#define DEV_NAME "misc_device"
#define MEM_SIZE 0x1000
#define MEM_CLEAR 0x1

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

	struct global_dev *dev = filp->private_data;

	if(count < 0 || count > MEM_SIZE)
	{
		ret = -EINVAL;
	}
	if(count > MEM_SIZE - p)
		count = MEM_SIZE - p;
	if(copy_from_user(&dev->memory + p,buffer,count))
		ret = -EINVAL;
	else{
		*offset += count;
		ret = count;
		printk("Write %u bytes from %lu\n",count,p);
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
	else{
		*offset += count;
		ret = count;
		printk("Read %u bytes from %lu\n",count,p);
	}
	return ret;
}

static loff_t misc_llseek(struct file *filp,loff_t offset,int arg)
{
	loff_t ret = 0;
	switch(arg){
	case 0:
		if(offset < 0 || offset > MEM_SIZE)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos=offset;
		break;
	case 1:
		if(offset < 0 || offset > MEM_SIZE)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
	case 2:
		if(offset < 0 || offset > MEM_SIZE)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos = MEM_SIZE + offset;
		ret = filp->f_pos;
		break;
	}
	return ret;
}

static long misc_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	struct global_dev *dev =filp->private_data;

	switch (cmd){
	case MEM_CLEAR:
	memset(dev->memory,0,MEM_SIZE);
	printk("global memeory is set to zero\n");
	break;
	default:
		return -EINVAL;
	}
	return 0;
}

static const struct file_operations fops={
	.open		= misc_open,
	.release	= misc_close,
	.read		= misc_read,
	.write		= misc_write,
	.compat_ioctl= misc_ioctl,
	.llseek		= misc_llseek,
	.owner		= THIS_MODULE
};
//1
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
	//2
	ret = misc_register(&misc);
	printk(DEV_NAME"initialized!\n");
	return ret;
}

static void __exit misc_exit(void)
{
	kfree(gdev);
	//3
	misc_deregister(&misc);
	printk("Goodbye kernel!");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan xing");

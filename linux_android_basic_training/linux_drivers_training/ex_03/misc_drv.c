/*
 * Filename:			misc_drv.c
 *
 * Copyright (C) 2014 Wistron
 * All rights reserved.
 * Description:			This file is a char device drvier.
 * Author/Created Date:	Longbin Li, <beangr@163.com> Jun26'14
 * Modification History:
 * Note:
 */

/* Include Files */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/miscdevice.h>

/* MACROS */
#define MEM_SIZE	0x1000

/* DEFINES */
#define MISC_READ	0X10001
#define MISC_WRITE	0X10002

struct misc_resource{
	struct miscdevice misc_dev;
	unsigned char mem[MEM_SIZE];
};
struct misc_resource *misc_vdp; 

/* INTERNAL FUNCTIONS */
/* open */
static int misc_open(struct inode *inode, struct file *filp)
{
	filp->private_data = misc_vdp;
    printk("%s\n", __func__);
    return 0;
}

/* close */
static int misc_close(struct inode *inode, struct file *filp)
{
    printk("%s\n", __func__);
    return 0;
}

/* read */
static ssize_t misc_read(struct file *filp, char __user *buf,
								size_t size, loff_t *ppos)
{
	ssize_t ret = 0;
	unsigned long p = *ppos;
	unsigned int count = size;
	struct misc_resource *dev = filp->private_data;

	if (p > MEM_SIZE) 
		return count ? -ENXIO : 0;
	if (count > MEM_SIZE - p)
		count = MEM_SIZE - p;

	if (copy_to_user(buf, (void *)(dev->mem + p), count)) {
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;
		printk("%s:\tread %u bytes from %lu\n", __func__, count, p);
	}
	return ret;
}

/* write */
static ssize_t misc_write(struct file *filp, char const __user *buf,
								size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	ssize_t ret = 0;
	struct misc_resource *dev = filp->private_data;

	if (p > MEM_SIZE) 
		return count ? -ENXIO : 0;
	if (count > MEM_SIZE - p)
		count = MEM_SIZE - p;

	if (copy_from_user(dev->mem + p, buf, count)) {
		return -EFAULT;
	} else {
		*ppos += count;
		ret = count;
		printk("%s:\twritten %u bytes from %lu\n", __func__, count, p);
	}
	return ret;
}

/* lseek */
static loff_t misc_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	printk("%s\n", __func__);
	switch(orig){
	case 0:
			if (offset < 0) {
				ret = -EINVAL;
				break;
			}
			if ((unsigned int)offset > MEM_SIZE) {
				ret = -EINVAL;
				break;
			}
			filp->f_pos = (unsigned int)offset;
			ret = filp->f_pos;
			break;
	case 1:
			if ((filp->f_pos + offset > MEM_SIZE)) {
				ret = -EINVAL;
				break;
			}
			if ((filp->f_pos + offset < 0)) {
				ret = -EINVAL;
				break;
			}
			filp->f_pos += offset;
			ret = filp->f_pos;
			break;
	default:
			ret = -EINVAL;
			break;
	}
	return ret;
}

/* ioctl */
static int misc_ioctl(struct file *filp, unsigned int cmd,
							unsigned long arg)
{
    switch(cmd) {
		case MISC_READ:
				{
					int rdata = 0x55;
					copy_to_user((int *)arg, &rdata, 4);
					printk("%s:\tMISC_READ\n", __func__);
				}
				break;
		case MISC_WRITE:
				{
					int data = 0;
					copy_from_user(&data, (int *)arg, 4);
					printk("%s:\tMISC_WRITE, wdata = %#x\n", __func__, data);
				}
				break;
		default:
					return -EINVAL;
    }
    return 0;
}

/* file_operations */
static struct file_operations misc_fops = {
    .owner		=	THIS_MODULE,
    .open		=	misc_open,
    .release	=	misc_close,
	.read		=	misc_read,
	.write		= 	misc_write,
	.llseek		=	misc_llseek,
    .unlocked_ioctl		=	misc_ioctl,
    //.ioctl		=	misc_ioctl,
};

static struct miscdevice misc_dev = {
	.minor	=	MISC_DYNAMIC_MINOR,
	.name	=	"misc_dev0",
	.fops	=	&misc_fops,
};

/* IMPLEMENTATION */
/* the entry function */
static int misc_init(void)
{
	int res;
	/* kmalloc */
	misc_vdp = kmalloc(sizeof(struct misc_resource), GFP_KERNEL);
	if (!misc_vdp) {
		res = -ENOMEM;
		goto fail_malloc;
	}
	memset(misc_vdp, 0, sizeof(struct misc_resource));

	/* misc_register(&(misc_vdp->misc_dev)); 无法创建设备节点 */
	misc_register(&misc_dev);

	printk("--------------------------------------------\n");
	printk("%s\n", __func__);
	return 0;

fail_malloc:misc_deregister(&misc_dev);
    return res;
}

/* the exit function */
static void misc_exit(void)
{
	//misc_deregister(&misc_vdp->misc_dev);
	misc_deregister(&misc_dev);

	printk("%s\n", __func__);
}
module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("GPL");

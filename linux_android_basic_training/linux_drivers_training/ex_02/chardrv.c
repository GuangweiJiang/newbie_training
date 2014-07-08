/*
 * Filename:			chardrv.c
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

/* MACROS */
#define MEM_SIZE	0x1000

/* DEFINES */
#define SCULL_READ	0X10001
#define SCULL_WRITE	0X10002

struct scull_resource{
	struct cdev scull_cdev;
	unsigned char mem[MEM_SIZE];
};
struct scull_resource *scull_info; 

static int major;

//static struct cdev scull_cdev;
static struct class *cls; 

/* INTERNAL FUNCTIONS */
/* open */
static int scull_open(struct inode *inode, struct file *filp)
{
	filp->private_data = scull_info;
    printk("%s\n", __func__);
    return 0;
}

/* close */
static int scull_close(struct inode *inode, struct file *filp)
{
    printk("%s\n", __func__);
    return 0;
}

/* read */
static ssize_t scull_read(struct file *filp, char __user *buf,
								size_t size, loff_t *ppos)
{
	ssize_t ret = 0;
	unsigned long p = *ppos;
	unsigned int count = size;
	struct scull_resource *dev = filp->private_data;

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
static ssize_t scull_write(struct file *filp, char const __user *buf,
								size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	ssize_t ret = 0;
	struct scull_resource *dev = filp->private_data;

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
static loff_t scull_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	printk("%s\n", __func__);
	switch(orig){
	case 0: /* SEEK_SET */
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
	case 1: /* SEEK_SUR */
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
	case 2: /* SEEK_END - Not supported */
			return -EINVAL;
	default:
			ret = -EINVAL;
			break;
	}
	return ret;
}

/* ioctl */
static long /*int*/ scull_ioctl(struct file *filp, unsigned int cmd,
							unsigned long arg)
{
    switch(cmd) {
		case SCULL_READ:
				{
					int rdata = 0x55;
					copy_to_user((int *)arg, &rdata, 4);
					printk("%s:\tSCULL_READ\n", __func__);
				}
				break;
		case SCULL_WRITE:
				{
					int data = 0;
					copy_from_user(&data, (int *)arg, 4);
					printk("%s:\tSCULL_WRITE, wdata = %#x\n", __func__, data);
				}
				break;
		default:
					return -EINVAL;
    }
    return 0;
}

/* file_operations */
static struct file_operations scull_fops = {
    .owner		=	THIS_MODULE,
    .open		=	scull_open,
    .release	=	scull_close,
	.read		=	scull_read,
	.write		= 	scull_write,
	.llseek		=	scull_llseek,
    .unlocked_ioctl		=	scull_ioctl,
};

/* IMPLEMENTATION */
/* the entry function */
static int scull_init(void)
{
    dev_t devno;
	int res;
    
    /* register a device number */
    res = alloc_chrdev_region(&devno, 0, 1, "scull");
	if (res < 0) {
		return res;
	}
    major = MAJOR(devno);

	/* kmalloc */
	scull_info = kmalloc(sizeof(struct scull_resource), GFP_KERNEL);
	if (!scull_info) {
		res = -ENOMEM;
		goto fail_malloc;
	}
	memset(scull_info, 0, sizeof(struct scull_resource));

    /* initialize the fops and cdev */
    cdev_init(&(scull_info->scull_cdev), &scull_fops);

    /* add the scull_cdev and devno to the kernel cdev list */
    if (cdev_add(&(scull_info->scull_cdev), devno, 1) < 0){
		res = -EFAULT;
		goto fail_cdev_add;
	}
    
    /* create a class and a device belonging to the class*/
    cls = class_create(THIS_MODULE, "scull"); 
    device_create(cls, NULL, devno, NULL, "scull0");

	printk("--------------------------------------------\n");
	printk("%s\n", __func__);
	return 0;

fail_cdev_add:kfree(scull_info);
fail_malloc:unregister_chrdev_region(devno, 1);
    return res;
}

/* the exit function */
static void scull_exit(void)
{
    cdev_del(&(scull_info->scull_cdev));
    unregister_chrdev_region(MKDEV(major, 0), 1);
    device_destroy(cls, MKDEV(major, 0));
    class_destroy(cls);
	kfree(scull_info);

	printk("%s\n", __func__);
}
module_init(scull_init);
module_exit(scull_exit);
MODULE_LICENSE("GPL");

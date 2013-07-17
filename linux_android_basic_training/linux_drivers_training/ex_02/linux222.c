//==========================================
// Filename:
//      linux222.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      The char device driver includes 3 parts of functions,
//1. make a node under /dev 
//	(use API such as class_create, class_device_create/device_create, class_destroy, class_device_destry/device destroy)
//2. add char device to kernel 
//	(use API such as register_chrdev_region, unregister_chrdev_region, cdev_alloc, cdev_init, cdev_add, cdev_del)
//3. support file operation functions (open, release, read, write, ioctl)
//
// Author/Created Date:
//      Jerry Liu, Jul.3rd 2013
//
// Modification History:
// 
//
//
// Note:
//    
//==========================================
//
// 
//
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
#include "cmd.h"
//
//
//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
#define BUFFERSIZE 200
#define DEVICE_MAJOR 249 /*设置一个主设备号*/
//
//
//-----------------------------------------------------------------
// CONSTANTS AND VARIABLES
//-----------------------------------------------------------------
static int device_major = DEVICE_MAJOR;

/*初始化并注册cdev,就是注册我们自己的字符设备*/
static struct class    *device_class;

/*定义一个与字符设备对应的结构体*/
struct device_cdev
{
	struct cdev cdev; /*cdev结构体，与字符设备对应*/

/*下面可以定义一些与字符设备相关的数据*/
	unsigned char mem[BUFFERSIZE];
};
struct device_cdev *device_cdevp; /*设备结构体指针*/
//
//
//-----------------------------------------------------------------
// OPEN FUNCTIONS :The function is provided for a driver to do any initialization in preparation.
//-----------------------------------------------------------------
int device_cdev_open( struct inode *node, struct file *filp )
{
/*将设备结构体指针赋给文件私有数据指针*/
	filp->private_data = device_cdevp; /*这样可以通过文件私有数据指针得到设备结构体*/
	return 0;
}
//
//
//-----------------------------------------------------------------
// RELEASE FUNCTIONS :The function is the reverse of open.
//-----------------------------------------------------------------
int device_cdev_release(struct inode *inode, struct file *filp )
{
	return 0;
}
//
//
//-----------------------------------------------------------------
// READ FUNCTIONS :The function is used to transfer data between the kernel address space and the user address space.
//-----------------------------------------------------------------
static ssize_t device_cdev_read( struct file *filp, char __user *buf, size_t size, loff_t *offset )
{
	unsigned long p = *offset; /*文件当前位置*/
	unsigned int count = size; /*要读取的长度*/
	int ret = 0;

	struct device_cdev *dev = filp->private_data; /*通过文件私有数据指针得到设备结构体，和前面的open对应*/

	if ( p >= BUFFERSIZE )
	return count ? -ENXIO:0;
	if ( count > BUFFERSIZE - p )
	count = BUFFERSIZE - p;

/*内核空间->用户空间*/
	if ( copy_to_user(buf, (void *)(dev->mem), count) )
	{
		ret = -EFAULT;
	}
	else
	{
		printk(KERN_INFO "read %u bytes(s) from %lu\n",count, p);
	}

	return ret;
}
//
//
//-----------------------------------------------------------------
// WRITE FUNCTIONS :The function is used to transfer data between the kernel address space and the user address space.
//-----------------------------------------------------------------
static ssize_t device_cdev_write( struct file *filp, const char __user *buf, size_t size, loff_t *offset )
{
	unsigned long p = *offset;
	unsigned int count = size;
	int ret = 0;

	struct device_cdev *dev = filp->private_data;

	if( p >= BUFFERSIZE )
		return 0;
	if (count > BUFFERSIZE - p )
		count = BUFFERSIZE - p;

	if ( copy_from_user( dev->mem, buf, count))
	{
		ret = -EFAULT;
	}
	else
	{
		printk(KERN_INFO "written %u bytes(s) from %lu\n",count, p);
	}

	return ret;
	}
//
//
//-----------------------------------------------------------------
// ioctl CONTROL FUNCTIONS :The function is used to control the devices.
//-----------------------------------------------------------------

static long  device_cdev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct device_cdev *dev = filp->private_data;

	switch(cmd)
	{
		case MEM_CLEAR:
		memset(dev->mem, 0 , BUFFERSIZE);
		printk( KERN_INFO "device is set to zero\n");
		break;

	default:
		return - EINVAL;
	}
	return 0;
}

/*文件操作结构体*/
static struct file_operations device_cdev_fops =
{
	.owner = THIS_MODULE,
	.open = device_cdev_open,
	.release = device_cdev_release,
	.read = device_cdev_read,
	.write = device_cdev_write,
	.unlocked_ioctl = device_cdev_ioctl,
};

static int device_cdev_setup( struct device_cdev *dev, int index )
{
	int err;
	dev_t devno = MKDEV(DEVICE_MAJOR, index);

	cdev_init( &dev->cdev, &device_cdev_fops );
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &device_cdev_fops; 
	err = cdev_add( &dev->cdev, devno, 1 );
	if (err)
	{
		printk(KERN_NOTICE "Error %d adding device %d", err, index);
	}

	device_class = class_create(THIS_MODULE, "device_class1");
	if (IS_ERR(device_class)) 
	{
        	printk(KERN_INFO "create class error\n");
        	return -1;
    	}
    	

	device_create(device_class, NULL, devno, NULL, "%s","ex02");   
    	return 0;
}
//
//
//-----------------------------------------------------------------
// LOAD FUNCTIONS :The function is used to load the modules.
//-----------------------------------------------------------------
static int __init device_cdev_init(void)
{
	int result;
	dev_t devno = MKDEV(device_major, 0);

/*申请设备号*/
	if ( device_major )
	{
		result = register_chrdev_region(devno, 1, "device_cdev");
	}
	else
	{
		result = alloc_chrdev_region( &devno, 0, 1, "device_cdev");
		device_major = MAJOR(devno);
	}
	if ( result < 0 )
	{
		return result;
	}

	device_cdevp = kmalloc(sizeof(struct device_cdev), GFP_KERNEL);
	if ( !device_cdevp )
	{
		result = -ENOMEM;
		goto fail_malloc;
	}
	memset(device_cdevp, 0, sizeof(struct device_cdev));
	device_cdev_setup(device_cdevp, 0);
	return 0;

	fail_malloc:
		unregister_chrdev_region(devno, 1);
		return result;
}
//
//
//-----------------------------------------------------------------
// UNINSTALL FUNCTIONS :The function is used to uninstall the modules.
//-----------------------------------------------------------------
static struct class    *device_class;

static void __exit device_cdev_exit(void)
{
	dev_t devno = MKDEV(DEVICE_MAJOR, 0);

	cdev_del(&device_cdevp->cdev);/*注销cdev*/
	kfree(device_cdevp);/*释放结构体内存*/
	unregister_chrdev_region(MKDEV(device_major, 0), 1);
	device_destroy(device_class, devno);
	class_destroy(device_class);
}

MODULE_AUTHOR("Jerry Liu");
MODULE_LICENSE("Dual BSD/GPL");

module_init(device_cdev_init);
module_exit(device_cdev_exit);

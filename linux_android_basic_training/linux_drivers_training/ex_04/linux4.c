//==========================================
// Filename:
//      linux4.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      This file will write a kernel driver and a test application,let them communication via ioctl.
//
// Author/Created Date:
//      Jerry Liu 30th Jul 2013
//
//
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <linux/slab.h>
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
#include "memdev.h"
//
//
//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------
static int mem_major = MEMDEV_MAJOR;

module_param(mem_major, int, S_IRUGO);

struct mem_dev *mem_devp; /*设备结构体指针*/

struct cdev cdev; 
//
//
//-----------------------------------------------------------------
// OPEN FUNCTIONS :The function is provided for a driver to do any initialization in preparation.
//-----------------------------------------------------------------
int mem_open(struct inode *inode, struct file *filp)
{
    struct mem_dev *dev;

/*获取次设备号*/
	int num = MINOR(inode->i_rdev);

	if (num >= MEMDEV_NR_DEVS) 
		return -ENODEV;
		dev = &mem_devp[num];

/*将设备描述结构指针赋值给文件私有数据指针*/
		filp->private_data = dev;

		return 0; 
}
//
//
//-----------------------------------------------------------------
// RELEASE FUNCTIONS :The function is the reverse of open.
//-----------------------------------------------------------------
int mem_release(struct inode *inode, struct file *filp)
{
	return 0;
}
//
//
//-----------------------------------------------------------------
// ioctl CONTROL FUNCTIONS :The function is used to control the  I/O devices.
//-----------------------------------------------------------------
static int memdev_ioctl(struct inode *inode, struct file *filp,
unsigned int cmd, unsigned long arg)
{

	int err = 0;
	int ret = 0;
	int ioarg = 0;

/* 检测命令的有效性 */
if (_IOC_TYPE(cmd) != MEMDEV_IOC_MAGIC) 
	return -EINVAL;
if (_IOC_NR(cmd) > MEMDEV_IOC_MAXNR) 
	return -EINVAL;

/* 根据命令类型，检测参数空间是否可以访问 */
if (_IOC_DIR(cmd) & _IOC_READ)
	err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	else 
	if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
if (err) 
	return -EFAULT;

/* 根据命令，执行相应的操作 */
	switch(cmd) {

/* 打印当前设备信息 */
	case MEMDEV_IOCPRINT:
		printk("<--- CMD MEMDEV_IOCPRINT Done--->\n\n");
	break;

/* 获取参数 */
	case MEMDEV_IOCGETDATA: 
		ioarg = 1101;
		ret = __put_user(ioarg, (int *)arg);
	break;

/* 设置参数 */
	case MEMDEV_IOCSETDATA: 
		ret = __get_user(ioarg, (int *)arg);
		printk("<--- In Kernel MEMDEV_IOCSETDATA ioarg = %d --->\n\n",ioarg);
	break;

	default:  
		return -EINVAL;
	}
	return ret;

}

/*文件操作结构体*/
static const struct file_operations mem_fops =
{
	.owner = THIS_MODULE,
	.open = mem_open,
	.release = mem_release,
	.unlocked_ioctl = memdev_ioctl,
};
//
//
//-----------------------------------------------------------------
// LOAD FUNCTIONS :The function is used to load the modules.
//-----------------------------------------------------------------
static int memdev_init(void)
{
	int result;
	int i;

	dev_t devno = MKDEV(mem_major, 0);

/* 静态申请设备号*/
	if (mem_major)
		result = register_chrdev_region(devno, 2, "memdev");
	else  /* 动态分配设备号 */
	{
		result = alloc_chrdev_region(&devno, 0, 2, "memdev");
		mem_major = MAJOR(devno);
	}  

	if (result < 0)
		return result;

/*初始化cdev结构*/
cdev_init(&cdev, &mem_fops);
cdev.owner = THIS_MODULE;
cdev.ops = &mem_fops;

/* 注册字符设备 */
cdev_add(&cdev, MKDEV(mem_major, 0), MEMDEV_NR_DEVS);

/* 为设备描述结构分配内存*/
mem_devp = kmalloc(MEMDEV_NR_DEVS * sizeof(struct mem_dev), GFP_KERNEL);
if (!mem_devp)    /*申请失败*/
{
	result =  - ENOMEM;
	goto fail_malloc;
}
memset(mem_devp, 0, sizeof(struct mem_dev));

/*为设备分配内存*/
for (i=0; i < MEMDEV_NR_DEVS; i++) 
{
	mem_devp[i].size = MEMDEV_SIZE;
	mem_devp[i].data = kmalloc(MEMDEV_SIZE, GFP_KERNEL);
	memset(mem_devp[i].data, 0, MEMDEV_SIZE);
}

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
static void memdev_exit(void)
{
	cdev_del(&cdev);   /*注销设备*/
	kfree(mem_devp);     /*释放设备结构体内存*/
	unregister_chrdev_region(MKDEV(mem_major, 0), 2); /*释放设备号*/
}

MODULE_AUTHOR("David Xie");
MODULE_LICENSE("GPL");

module_init(memdev_init);
module_exit(memdev_exit);

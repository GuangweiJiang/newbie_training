//==========================================
// Filename:
//      linux3.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      Use "misc_register" to add a char device to kernel.
//
// Author/Created Date:
//      Jerry Liu, Jul.5th 2013
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
#include <linux/miscdevice.h>
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
//
//
//-----------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------
#define MISC_NAME "miscdriver"
#define misc_size 0x1000

struct misc_cdev
{
  char mem[200];		
  int size;
};

//
//
//-----------------------------------------------------------------
// OPEN FUNCTION:The function is provided for a driver to do any initialization in preparation.
//-----------------------------------------------------------------
static int misc_open(struct inode *inode, struct file *file)
{
	printk("misc open\n");
	return 0;
}
//
//
//-----------------------------------------------------------------
// RELEASE FUNCTION:The function is the reverse of open.  
//-----------------------------------------------------------------
int misc_release(struct inode *inode, struct file *filp )
{
        return 0;
}
//
//
//-----------------------------------------------------------------
// READ FUNCTION:The function is used to transfer data between the kernel address space and the user address space.
//-----------------------------------------------------------------
static ssize_t misc_read( struct file *filp, char __user *buf, size_t size, loff_t *offset )
{
        int ret = 0;
		unsigned int count = size;

        struct misc_cdev *dev = filp->private_data; /*通过文件私有数据指针得到设备结构体，和前面的open对应*/

/*内核空间->用户空间*/
        if ( copy_to_user(buf,(void *) (dev->mem), (unsigned long) count) )
        {
                ret = -EFAULT;
        }
        else
        {
                printk(KERN_INFO "read %u bytes(s) \n",count);
        }

        return ret;
}
//
//
//-----------------------------------------------------------------
// WRITE FUNCTION:The function is used to transfer data between the kernel address space and the user address space.
//-----------------------------------------------------------------
static ssize_t misc_write( struct file *filp, const char __user *buf, size_t size, loff_t *offset )
{
        int ret = 0;
		unsigned int count = size;
        struct misc_cdev *dev = filp->private_data;
        if ( copy_from_user( dev->mem, buf, count))
        {
                ret = -EFAULT;
        }
        else
        {
                printk(KERN_INFO "written %u bytes(s) \n",count);
        }

        return ret;
        }
//
//
//-----------------------------------------------------------------
// LOCATE FUNCTION:The function is used to locate the current position.
//-----------------------------------------------------------------
static loff_t misc_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	switch (orig) 
	{
	case 0:  /*相对文件开始位置偏移*/
		if (offset<0)
		{
			ret = - EINVAL;
			break;
		}
		if ((unsigned int)offset > misc_size)
		{
			ret =-EINVAL;
			break;
		}
		filp->f_pos = (unsigned int)offset;
		ret = filp->f_pos;
		break;
	case 1:  /*相对文件当前位置偏移*/ 
		if ((filp->f_pos + offset)>misc_size)
		{
			ret = -EINVAL;
			break;
		}
		if ((filp->f_pos + offset)< 0)
		{
			ret = -EINVAL;
			break;
		}
		filp->f_pos +=offset;
		ret =filp->f_pos;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}


static const struct file_operations misc_fops =
{
    .owner   =   THIS_MODULE,
    .open    =   misc_open,
	.release =   misc_release,
	.read    =   misc_read,
	.write   =   misc_write,
	.llseek  =   misc_llseek,
};

static struct miscdevice misc_dev =
{
	.minor = MISC_DYNAMIC_MINOR,
	.name = MISC_NAME,
	.fops = &misc_fops,
};
//
/ 
//-----------------------------------------------------------------
// LOAD FUNCTION:The function is used to load the modules.
//-----------------------------------------------------------------
static int __init misc_init(void)
{
  	int ret;
	ret = misc_register(&misc_dev);
	if (ret)
	{
  		printk("misc_register error\n");
  		return ret;
	}

  	return 0;
}
//
//
//-----------------------------------------------------------------
// UNINSTALL FUNCTION:The function is used to uninstall the modules.
//-----------------------------------------------------------------
static void __exit misc_exit(void)
{
  	misc_deregister(&misc_dev);
}

module_init(misc_init);
module_exit(misc_exit);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jerry Liu");

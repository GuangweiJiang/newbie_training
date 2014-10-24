//==========================================
// Filename:
// chardriver
//
// Copyright (C) 2006 Wistron
// All rights reserved.
//
// Description:
// 
//
// Author/Created Date:
// Jimmy Jiang, 7.29'14
//
// Modification History:
//
//
//
// Note:
//
//==========================================
//
//--------------------------------------------------------------------------------------
// Include Files
//--------------------------------------------------------------------------------------
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/memory.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>
//#include <linux/system.h>
#include <linux/mm.h>
#include <linux/timer.h>
#include <linux/kernel.h>
//-----------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------
#define GLOBALMEM_MAJOR 201
//-----------------------------------------------------------------
// CONSTANTS AND VARIABLES
//-----------------------------------------------------------------
static struct class *globalmem_class;      //定义一个class类结构体变量   
static struct device *globalmem_class_dev; //定义一个类设备结构体变量
static int globalmem_major = GLOBALMEM_MAJOR;/*预设的globalmem的主设备号*/
struct globalmem_dev  
{  
		struct cdev cdev;  //cdev结构体  
		atomic_t counter;
		struct timer_list s_timer;
};


struct globalmem_dev *globalmem_devp;
//-----------------------------------------------------------------
// OPEN FUNCTIONS :The function is to open globalmem device file
//-----------------------------------------------------------------

static void     second_timer_handle(unsigned long arg)
{
		printk("%s %d\n",__func__,__LINE__);
		mod_timer(&globalmem_devp->s_timer,jiffies + HZ);  //修改定时器的到期时间，在新的被传入的expire到来后才执行定时器函数
		atomic_inc(&globalmem_devp->counter); 		   //对counter加1
		//printk("%s",__FUNCTION__);

}
int globalmem_open(struct inode *inode,struct file *filp)
{  		
		printk("%s %d\n",__func__,__LINE__);
		filp->private_data = globalmem_devp; 		
		init_timer(&globalmem_devp->s_timer);			//初始化定时器
		globalmem_devp->s_timer.function = &second_timer_handle;//赋值定时器结构体的处理函数
		globalmem_devp->s_timer.expires = jiffies + HZ;		//赋值定时器结构体的到期时间
		add_timer(&globalmem_devp->s_timer);			//增加定时器
		atomic_set(&globalmem_devp->counter,0);			//将counter清零
		printk("%s %d\n",__func__,__LINE__);
		printk("globalmem_open\n");
		//filp->private_data = globalmem_devp; //将设备结构体的指针赋值给文件指针 
		return 0;
} 
//-----------------------------------------------------------------
// RELEASE FUNCTIONS :The function is to close globalmem device file
//-----------------------------------------------------------------
int globalmem_release(struct inode *inode,struct file *filp)
{		printk("%s %d\n",__func__,__LINE__);
		del_timer(&globalmem_devp->s_timer);			//删除定时器结构体
		return 0;
}
//-----------------------------------------------------------------
// READ FUNCTIONS :The function is to read data from globalmem device to user space
//-----------------------------------------------------------------
static ssize_t globalmem_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{  
		int counter;
		counter = atomic_read(&globalmem_devp->counter);
		if(put_user(counter,(int*)buf))
			return -EFAULT;
		else
			return sizeof(unsigned int);
}  
//-----------------------------------------------------------------
// SET UP FUNCTIONS :The function is to initialise and set up a char device
//-----------------------------------------------------------------

static const struct file_operations globalmem_fops =
{
		.owner=THIS_MODULE,
		.read = globalmem_read, 
		.open = globalmem_open, 
		.release = globalmem_release,
};
static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)  
{  
		int err,devno = MKDEV(globalmem_major,index); //把设备号赋值给devno 
		cdev_init(&dev->cdev,&globalmem_fops); //初始化cdev
		dev->cdev.owner = THIS_MODULE;  
		dev->cdev.ops = &globalmem_fops;      //建立cdev 与file_operation之间的联系
		printk("%s %d\n",__func__,__LINE__);
		err = cdev_add(&dev->cdev,devno,1);  //向系统申请添加一个cdev
		if(err)  
		{ 
				printk(KERN_NOTICE"Error %d adding LED %d",err,index);  
		}  

}
//-----------------------------------------------------------------
// FUNCTIONS :The function is used to load the modules
//-----------------------------------------------------------------
static int globalmem_init(void)

{		int result;  
		dev_t devno = MKDEV(globalmem_major,0);  //使用此宏可以通过主设备号和次设备号生成dev_t
		if(globalmem_major)  
		{  
				result = register_chrdev_region(devno,1,"globalmem");  //向系统申请设备号
		}  
		else  //动态申请设备号  
		{  
				result = alloc_chrdev_region(&devno,0,1,"globalmem");  
				globalmem_major = MAJOR(devno);  
		}  
		if(result < 0)  
		{  
				return result;  //申请失败返回一个负数
		}  

		globalmem_devp = kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL); //向内核申请globalmem结构体的内存  
		if(!globalmem_devp)  
		{  
				result = -ENOMEM;  
				goto fail_malloc;  
		}  
		printk("%s %d\n",__func__,__LINE__);
		memset(globalmem_devp,0,sizeof(struct globalmem_dev));  //初始化申请的内存
		globalmem_setup_cdev(globalmem_devp,0);      //向系统申请添加关于globalmem的cdev
		printk("%s %d\n",__func__,__LINE__);
		globalmem_class = class_create(THIS_MODULE, "globalmem_sys_class");        
		if (IS_ERR(globalmem_class))    
				return PTR_ERR(globalmem_class);    

		globalmem_class_dev = device_create(globalmem_class, NULL, MKDEV(globalmem_major, 0), NULL, "globalmem_dev");       
		if (unlikely(IS_ERR(globalmem_class_dev)))    
				return PTR_ERR(globalmem_class_dev);  
		printk("%s %d\n",__func__,__LINE__);
		return 0;  

		fail_malloc:unregister_chrdev_region(devno,1);  
		return result;  
}
//-----------------------------------------------------------------
// FUNCTIONS :The function is used to uninstall the modules
//-----------------------------------------------------------------
static void globalmem_exit(void)
{  
		cdev_del(&globalmem_devp->cdev); //注销cdev  
		kfree(globalmem_devp);          //释放设备结构体内存  
		printk("%s %d\n",__func__,__LINE__);
		unregister_chrdev_region(MKDEV(globalmem_major,0),1); //释放设备号  
		device_unregister(globalmem_class_dev);    
		class_destroy(globalmem_class);
}  

MODULE_LICENSE("Dual BSD/GPL");
module_init(globalmem_init);
module_exit(globalmem_exit);

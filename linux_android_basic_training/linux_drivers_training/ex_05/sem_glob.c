//==========================================
// Filename:
// sem_glob.c
//
// Copyright (C) 2006 Wistron
// All rights reserved.
//
// Description:
//Use "misc_register" to add a char device to kernel, and use "echo" to communicate with driver.
//(use API such as misc_register, misc_deregister)
//
// Author/Created Date:
// Jimmy Jiang, 7.18'14
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
#include <linux/miscdevice.h>
#include <linux/module.h>/*For module specific items*/
#include <linux/types.h>/*for standard types (like size_t) */
#include <linux/kernel.h>/*For printk/panic/...*/
#include <linux/device.h>/*For struct class*/
#include <linux/string.h>/*For strlen...*/
#include <linux/errno.h> /*For the -ENODEV/...value*/
#include <linux/init.h>/*For __init/__exit/....*/
#include <linux/fs.h>/*For struct file_operations*/
#include <linux/cdev.h>/*For struct cdev/cdev_init/...*/
#include <asm/uaccess.h>/*For copy_to_user/ ...*/
#include <linux/errno.h>
#include <linux/slab.h> /*for kmalloc()*/
#include <linux/semaphore.h>/*for down() up() */
#include <asm/semaphore.h>
//-----------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------
#define GLOBALMEM_SIZE 0X1000 /*全局内存最大4KB*/  
#define MEM_CLEAR 0x1   
//#define GLOBALMEM_MINOR 12
#define DEV_NAME "mis_drv"

//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------




//-----------------------------------------------------------------
// CONSTANTS AND VARIABLES
//-----------------------------------------------------------------
//static struct class *globalmem_class;      //定义一个class类结构体变量   
//static struct device *globalmem_class_dev; //定义一个类设备结构体变量
//static int globalmem_major = GLOBALMEM_MAJOR;/*预设的globalmem的主设备号*/



struct globalmem_dev  
{  
   struct cdev cdev;  //cdev结构体  
   unsigned char mem[GLOBALMEM_SIZE];  //全局内存  
   struct semaphore sem;
};


struct globalmem_dev *globalmem_devp;
//-----------------------------------------------------------------
// OPEN FUNCTIONS :The function is to open globalmem device file
//-----------------------------------------------------------------

int misc_open(struct inode *inode,struct file *filp)
{  

 filp->private_data = globalmem_devp; //将设备结构体的指针赋值给文件指针
 printk(KERN_INFO "hello.world.open\n"); 
 return 0;
} 
//-----------------------------------------------------------------
// RELEASE FUNCTIONS :The function is to close globalmem device file
//-----------------------------------------------------------------
int misc_release(struct inode *inode,struct file *filp)
{
 return 0;
}

//-----------------------------------------------------------------
// READ FUNCTIONS :The function is to read data from globalmem device to user space
//-----------------------------------------------------------------
static ssize_t misc_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{  
 unsigned long p = *ppos;  
 unsigned int count = size;  
 int ret = 0;  

 struct globalmem_dev *dev = filp->private_data; //获得设备结构体指针  
   
 if(p >GLOBALMEM_SIZE)  //分析和获取有效的写长度  
 {  
  return count ? -ENXIO:0;  
 }  
 if(count > GLOBALMEM_SIZE - p)  
 {  
  count = GLOBALMEM_SIZE - p;  
 }  
 if(down_interruptible(&dev->sem))
	return -ERESTARTSYS;
   
 if(copy_to_user(buf,(void *)(dev->mem+p),count))  //内核空间->用户空间  
 {  
  ret = -EFAULT;  
 }  
 else  
 {  
  *ppos += count;  
  ret = count;  
  printk(KERN_INFO "read   %d bytes(s) from   %lu\n",count,p);  
 }
  up(&dev->sem);  
 printk(KERN_INFO "hello.world.read\n");
 return ret;  
}  
//-----------------------------------------------------------------
// READ FUNCTIONS :The function is to write data to globalmem device
//-----------------------------------------------------------------
static ssize_t misc_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{  
 unsigned long p = *ppos;  
 unsigned int count = size;  
 int ret=0;  
 struct globalmem_dev *dev = filp->private_data;  
   
 if(p >= GLOBALMEM_SIZE)  //分析和获取有效的写长度  
 {  
  return count? -ENXIO:0;  
 }  
   
 if(count > GLOBALMEM_SIZE - p)  
 {  
  count = GLOBALMEM_SIZE - p;  
 }   
  if(down_interruptible(&dev->sem))
	return -ERESTARTSYS;
 if(copy_from_user(dev->mem + p,buf,count)) // 用户空间->内核空间  
 {  
  ret = -EFAULT; 
   printk(KERN_INFO "hello.world.write successful\n"); 
 }  
 else  
 {  
  *ppos =+ count;  
  ret = count;  
  printk(KERN_INFO "written %d bytes(s) from %lu\n",count,p);  
 } 
  up(&dev->sem); 
 printk(KERN_INFO "hello.world.write\n"); 
 return ret;  
} 
static loff_t  misc_llseek(struct file *filp,loff_t offset,int orig)
{  
 loff_t ret = 0;  
 switch(orig)  
 {  
  case 0:   //相对文件开始位置偏移  
   if(offset <0 )  
   {  
    ret = -EINVAL;  
    break;  
   }  
     
   if((unsigned int )offset > GLOBALMEM_SIZE)  
   {  
    ret = - EINVAL;  
    break;  
   }  
   filp->f_pos = (unsigned int)offset;  
   ret = filp->f_pos;  
   break;  
     
  case 1:   //相对文件当前位置偏移  
   if((filp->f_pos + offset) > GLOBALMEM_SIZE)  
   {  
    ret = -EINVAL;  
    break;  
   }  
   if((filp->f_pos + offset)<0)  
   {  
    ret = -EINVAL;  
    break;  
   }  
   filp->f_pos +=offset;  
   ret = filp->f_pos;  
   break;  
  default:  
   ret = -EINVAL;  
   break;   
 }  
 return ret;  
}  
//-----------------------------------------------------------------
// SET UP FUNCTIONS :The function is to initialise and set up a char device
//-----------------------------------------------------------------
 
 
 static  struct file_operations fops =
{
 .owner=THIS_MODULE,
 .llseek = misc_llseek,
 .read = misc_read, 
 .write = misc_write, 
 .open = misc_open, 
 .release = misc_release,
};

static struct miscdevice    misc =
{	.minor = MISC_DYNAMIC_MINOR,
	.name  =DEV_NAME,
	.fops  =&fops

};


//-----------------------------------------------------------------
// FUNCTIONS :The function is used to load the modules
//-----------------------------------------------------------------
static int globalmem_init(void)

{
	int result;
	globalmem_devp = kmalloc(sizeof(struct globalmem_dev),GFP_KERNEL); //向内核申请globalmem结构体的内存  
 	if(!globalmem_devp)  
 	{  
  		result = -ENOMEM;  
  		printk("bad address\n");  
 	}  
	misc_register(&misc);
	init_MUTEX(&globalmem_devp->sem);
	printk("globalmem_init\n");
	return 0; 
}
//-----------------------------------------------------------------
// FUNCTIONS :The function is used to uninstall the modules
//-----------------------------------------------------------------
//static struct class    *device_class;
static void  globalmem_exit(void)
{  
 	misc_deregister(&misc);
 	kfree(globalmem_devp);
	printk("globalmem_exit\n");
 
}  

MODULE_LICENSE("Dual BSD/GPL");
module_init(globalmem_init);
module_exit(globalmem_exit);

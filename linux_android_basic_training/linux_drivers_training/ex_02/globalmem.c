//==========================================
// Filename:
// chardriver
//
// Copyright (C) 2006 Wistron
// All rights reserved.
//
// Description:
// This is a simple char device driver.include below 3 parts of functions,
//1. make a node under /dev 
//	(use API such as class_create, class_device_create/device_create, class_destroy, class_device_destry/device destroy)
//2. add char device to kernel 
//	(use API such as register_chrdev_region, unregister_chrdev_region, cdev_alloc, cdev_init, cdev_add, cdev_del)
//3. support file operation functions (open, release, read, write, ioctl)
//
// Author/Created Date:
// Jimmy Jiang, 6.26'14
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
#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/device.h>

//-----------------------------------------------------------------
// MACROS
//-----------------------------------------------------------------
#define GLOBALMEM_SIZE 0X1000 /*全局内存最大4KB*/  
#define MEM_CLEAR 0x1   
#define GLOBALMEM_MAJOR 201

//-----------------------------------------------------------------
// DEFINES
//-----------------------------------------------------------------




//-----------------------------------------------------------------
// CONSTANTS AND VARIABLES
//-----------------------------------------------------------------
static struct class *globalmem_class;      //定义一个class类结构体变量   
static struct device *globalmem_class_dev; //定义一个类设备结构体变量
static int globalmem_major = GLOBALMEM_MAJOR;/*预设的globalmem的主设备号*/



struct globalmem_dev  
{  
 struct cdev cdev;  //cdev结构体  
 unsigned char mem[GLOBALMEM_SIZE];  //全局内存  
};


struct globalmem_dev *globalmem_devp;
//-----------------------------------------------------------------
// OPEN FUNCTIONS :The function is to open globalmem device file
//-----------------------------------------------------------------

int globalmem_open(struct inode *inode,struct file *filp)
{  
printk(KERN_INFO "hello.world7\n");
 filp->private_data = globalmem_devp; //将设备结构体的指针赋值给文件指针 
 return 0;
} 
//-----------------------------------------------------------------
// RELEASE FUNCTIONS :The function is to close globalmem device file
//-----------------------------------------------------------------
int globalmem_release(struct inode *inode,struct file *filp)
{
 return 0;
}
//-----------------------------------------------------------------
// IOCTL FUNCTIONS :The function is to transfer device control informatin
//-----------------------------------------------------------------
static long globalmem_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{  
 struct globalmem_dev *dev = filp->private_data; //获得设备结构体指针  
 printk(KERN_INFO "hello.world6\n");
 switch(cmd)  
 {  
  case  MEM_CLEAR:  
   memset(dev->mem,0,GLOBALMEM_SIZE);  
   printk(KERN_INFO "globalmem is set to zero\n");  
   break;  
  default:  
   return -EINVAL;  
 }  
 return 0;  
}  
//-----------------------------------------------------------------
// READ FUNCTIONS :The function is to read data from globalmem device to user space
//-----------------------------------------------------------------
static ssize_t globalmem_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
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
 return ret;  
}  
//-----------------------------------------------------------------
// READ FUNCTIONS :The function is to write data to globalmem device
//-----------------------------------------------------------------
static ssize_t globalmem_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
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
   
 if(copy_from_user(dev->mem + p,buf,count)) // 用户空间->内核空间  
 {  
  ret = -EFAULT;  
 }  
 else  
 {  
  *ppos =+ count;  
  ret = count;  
  printk(KERN_INFO "written %d bytes(s) from %lu\n",count,p);  
 }  
 return ret;  
} 
static loff_t  globalmem_llseek(struct file *filp,loff_t offset,int orig)
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
 
 static const struct file_operations globalmem_fops =
{
 .owner=THIS_MODULE,
 .llseek = globalmem_llseek,
 .read = globalmem_read, 
 .write = globalmem_write, 
 .unlocked_ioctl = globalmem_ioctl,  
 .open = globalmem_open, 
 .release = globalmem_release,
};
static void globalmem_setup_cdev(struct globalmem_dev *dev,int index)  
{  
 int err,devno = MKDEV(globalmem_major,index); //把设备号赋值给devno 
 cdev_init(&dev->cdev,&globalmem_fops); //初始化cdev
 dev->cdev.owner = THIS_MODULE;  
 dev->cdev.ops = &globalmem_fops;      //建立cdev 与file_operation之间的联系
 printk(KERN_INFO "hello.world3\n");
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

{int result;  
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
   //globalmem_class = class_create(THIS_MODULE, "globalmem_sys_class");
    //if(IS_ERR(globalmem_class)) {
            //printk("Err: failed in creating class.\n");
             //goto fail_malloc;
  //} 
  /* register your own device in sysfs, and this will cause udev to create corresponding device node */
  
 memset(globalmem_devp,0,sizeof(struct globalmem_dev));  //初始化申请的内存
 globalmem_setup_cdev(globalmem_devp,0);      //向系统申请添加关于globalmem的cdev
 //device_create(globalmem_class, NULL, MKDEV(globalmem_major, 0), NULL, "globalmem");
globalmem_class = class_create(THIS_MODULE, "globalmem_sys_class");        
    if (IS_ERR(globalmem_class))    
        return PTR_ERR(globalmem_class);    
      
    globalmem_class_dev = device_create(globalmem_class, NULL, MKDEV(globalmem_major, 0), NULL, "globalmem_dev");       
    if (unlikely(IS_ERR(globalmem_class_dev)))    
        return PTR_ERR(globalmem_class_dev);  
  printk (KERN_INFO "Registered character driver\n");
 printk(KERN_INFO "hello.world1\n");
 return 0;  
   
 fail_malloc:unregister_chrdev_region(devno,1);  
 return result;  
}
//-----------------------------------------------------------------
// FUNCTIONS :The function is used to uninstall the modules
//-----------------------------------------------------------------
//static struct class    *device_class;
static void  globalmem_exit(void)
{  
 int devno = MKDEV(globalmem_major,MKDEV(globalmem_major,0));
 cdev_del(&globalmem_devp->cdev); //注销cdev  
 kfree(globalmem_devp);          //释放设备结构体内存  
 printk(KERN_INFO "hello.world2\n");
 unregister_chrdev_region(MKDEV(globalmem_major,0),1); //释放设备号  
 device_unregister(globalmem_class_dev);    
    class_destroy(globalmem_class);
}  

MODULE_LICENSE("Dual BSD/GPL");
module_init(globalmem_init);
module_exit(globalmem_exit);

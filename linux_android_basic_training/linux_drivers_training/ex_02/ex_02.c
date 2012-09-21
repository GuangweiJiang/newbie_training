/*
 * file name: ex_02.c
 * purpose: a simple driver of char
 * creator: Allan xing
 * create time: 2012-09-17
 * modify history: 2012-09-19
 * 				   2012-09-21
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/memory.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define DEV_NAME 	"chardev"
#define MEM_SIZE 	0x1000//The size of the global memory  
#define MEM_CLEAR  	0x1   //clear the memory
#define MAJOR_NUM 	0
#define MINOR_NUM 	0

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

//make device structure
struct global_dev{
	struct cdev test_cdev;
	char 	memory[MEM_SIZE];
};
struct global_dev gdev;
dev_t devno;


static int char_open(struct inode *node, struct file *file)
{
	printk("open device!\n");
	return 0;
}
static int char_close(struct inode *node, struct file *file)
{
	printk("close device!\n");
	return 0;
}

static ssize_t char_read(struct file *file,char __user* buffer,size_t size,loff_t *offset)
{
	unsigned long p = *offset;
        unsigned int count = size;
	int ret = 0;
	int nread;
	if(p >= MEM_SIZE)
		return 0;
	if(count > MEM_SIZE - p)
		count = MEM_SIZE - p;
	nread = copy_to_user(buffer,gdev.memory + p, count);
	if(nread>0)
		ret = count - nread;
	else{
		p += count;
		ret = count;
	}
	printk("Read %u bytes from %lu\n",count,p);
	return ret;
}
static ssize_t char_write(struct file *file,const char __user* buffer,size_t size,loff_t *offset)
{
	unsigned long p = *offset;
        unsigned int count = size;
	int ret = 0;
	int nwrite;
	if(p >= MEM_SIZE)
		return 0;
	if(count > MEM_SIZE - p)
		count = MEM_SIZE - p;
	nwrite = copy_from_user(gdev.memory + p,buffer, count);
	if(nwrite>0)
		ret = count - nwrite;
	else{
		p += count;
		ret = count;
	}
	printk("Write %u bytes from %lu\n",count,p);
	return ret;
}
static loff_t char_llseek(struct file* file,loff_t offset,int arg)
{
	loff_t ret=0;
	switch (arg){
		case 0:
			if(offset<0 || offset > MEM_SIZE)
			{
				ret=-EINVAL;
				break;
			}
			file->f_pos=offset;
			ret=file->f_pos;
			break;
		case 1:
			if(offset<0 || offset > MEM_SIZE)
			{
				ret=-EINVAL;
				break;
			}
			file->f_pos +=offset;
			ret = file->f_pos;
			break;
		case 2:
			if(offset<0 || offset > MEM_SIZE)
			{
				ret=-EINVAL;
				break;
			}
			file->f_pos = MEM_SIZE + offset;
			ret = file->f_pos;
			break;
	}
	return ret;
}
static long char_ioctl(struct file *file,unsigned int cmd,unsigned long arg)
{
	switch (cmd){
	case MEM_CLEAR:
		memset(gdev.memory,0,MEM_SIZE);
		printk("global memory is set to zero\n");
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static const struct file_operations test_fops = {
	.open		= char_open,
	.release	= char_close,
	.read		= char_read,
	.write		= char_write,
	.llseek		= char_llseek,
	.compat_ioctl		=char_ioctl,
	.owner		= THIS_MODULE
};

static void global_setup_cdev(struct global_dev dev,int index)
{
        int ret = 0;
        //2 register device
	//initialize device
	cdev_init(&gdev.test_cdev,&test_fops);
	//add cdev to kernel
	ret = cdev_add(&gdev.test_cdev,devno,1);
	if(ret<0){
		printk("add  error!\n");
		goto err1;
	}
	printk("Hello kernel!\n");
err1:
	unregister_chrdev_region(devno,1);//if registration failed,unregister it
}
static int __init char_init(void)
{
	int ret=0;
	//1 register device
	if(MAJOR_NUM){
		devno = MKDEV(MAJOR_NUM,MINOR_NUM);
		ret = register_chrdev_region(devno,1,DEV_NAME);
	}else{
		ret = alloc_chrdev_region(&devno,MINOR_NUM,1,DEV_NAME);
	}
	if(ret<0){
		printk("register error!\n");
		goto err0;
	}
	printk("major=%d,minor=%d\n",MAJOR(devno),MINOR(devno));
	global_setup_cdev(gdev,0);
	return 0;
err0:
	return ret;
}

static void __exit char_exit(void)
{
	//1 delete the cdev from kernel
	cdev_del(&gdev.test_cdev);
	//2 Cancellation of the device number
	unregister_chrdev_region(devno,1);

	printk("Good bye kernel!\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan");

/*
 * file name: ex_04.c
 * purpose: Create a module of char dirver to test ioctl function
 * creator: Allan xing
 * create time: 2012-09-27
 * modify history: 2012-10-05 Code completion
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/memory.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#define DEV_NAME 	"chardev"
#define MEM_SIZE 	0x1000//The size of the global memory  
#define MAJOR_NUM 	0
#define MINOR_NUM 	0

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define IOCTL_CHARDEV_MAGIC 'k'
#define IOCTL_CHARDEV_MAX_NR 2

#define IOCTL_CHARDEV_CLEAR _IO(IOCTL_CHARDEV_MAGIC,1)
#define IOCTL_CHARDEV_OFFSET _IO(IOCTL_CHARDEV_MAGIC,2)

//make device structure
struct global_dev
{
	struct cdev test_cdev;
	char 	memory[MEM_SIZE];
};
struct global_dev gdev;
struct global_dev *global_devp;
struct class *driver_class;
dev_t devno;


static int char_open(struct inode *node, struct file *file)
{
	file->private_data = global_devp;
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
	struct global_dev *dev = file->private_data;
	unsigned long p = *offset;
	unsigned int count = size;
	int ret = 0;
	int nread;
	if(p >= MEM_SIZE)
	{
		return 0;
	}
	if(count > MEM_SIZE - p)
	{
		count = MEM_SIZE - p;
	}
	nread = copy_to_user(buffer,dev->memory + p, count);
	if(nread>0)
	{
		ret = count - nread;
	}
	else
	{
		*offset += count;
		ret = count;
	}
	printk("Read %u bytes from %lu\n",count,p);
	return ret;
}
static ssize_t char_write(struct file *file,const char __user* buffer,size_t size,loff_t *offset)
{
	struct global_dev *dev = file->private_data;
	unsigned long p = *offset;
	unsigned int count = size;
	int ret = 0;
	int nwrite;
	if(p >= MEM_SIZE)
	{
		return 0;
	}
	if(count > MEM_SIZE - p)
	{
		count = MEM_SIZE - p;
	}
	nwrite = copy_from_user(dev->memory + p,buffer, count);
	if(nwrite>0)
	{
		ret = count - nwrite;
	}
	else
	{
		*offset += count;
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
	int ret = 0;
	struct global_dev *dev = file->private_data;

	if(_IOC_TYPE(cmd) != IOCTL_CHARDEV_MAGIC)return -EINVAL;
	if(_IOC_NR(cmd) > IOCTL_CHARDEV_MAX_NR)return -EINVAL;

	switch(cmd)
	{
	case IOCTL_CHARDEV_CLEAR:
		memset(dev->memory,0,MEM_SIZE);
		file->f_pos = 0;
		printk("clear the memory!\n");
		ret = 0;
		break;
	case IOCTL_CHARDEV_OFFSET:
		file->f_pos += (int)arg;
		ret = file->f_pos;
		printk("change offset!\n");
		break;
	default:
		printk("error cmd\n");
		ret = -EINVAL;
		break;
	}
	return ret;
}

static const struct file_operations test_fops = {
	.open		= char_open,
	.release	= char_close,
	.read		= char_read,
	.write		= char_write,
	.llseek		= char_llseek,
	.unlocked_ioctl		=char_ioctl,//?
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
	if(ret<0)
	{
		printk("add  error!\n");
		goto err1;
	}
err1:
	unregister_chrdev_region(devno,1);//if registration failed,unregister it
}
static int __init char_init(void)
{
	int ret=0;
	//1 register device
	if(MAJOR_NUM)
	{
		devno = MKDEV(MAJOR_NUM,MINOR_NUM);
		ret = register_chrdev_region(devno,1,DEV_NAME);
	}
	else
	{
		ret = alloc_chrdev_region(&devno,MINOR_NUM,1,DEV_NAME);
	}
	if(ret<0)
	{
		printk("register error!\n");
		goto err0;
	}
	global_devp = kmalloc(sizeof(struct global_dev),GFP_KERNEL);
	if(!global_devp)
	{
		ret = -EINVAL;
		goto err0;
	}
	global_setup_cdev(gdev,0);

	//Creating a device node
	driver_class = class_create(THIS_MODULE,DEV_NAME);
	device_create(driver_class,NULL,devno,NULL,DEV_NAME);
	printk("major=%d,minor=%d\n",MAJOR(devno),MINOR(devno));
	printk("Hello kernel!\n");
	return 0;
err0:
	unregister_chrdev_region(devno,1);//if registration failed,unregister it
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

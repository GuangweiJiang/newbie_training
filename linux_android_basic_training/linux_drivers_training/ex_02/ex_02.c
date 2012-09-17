#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>

unsigned int major = 0;
unsigned int minor = 0;
dev_t devno;

struct cdev test_dev;
struct file_operations test_fops;

static int char_open(void)
{
	return 0;
}
static int char_close(void)
{
	return 0;
}

static ssize_t char_read(void)
{
	return 0;
}
static ssize_t char_write(void)
{
	return 0;
}

static long char_iotcl(void)
{
	return 0;
}

static const struct file_operation fops = {
	.open		= char_open,
	.close		= char_close,
	.read		= char_read,
	.write		= char_write,
	.compat_iotcl=char_iotcl,
	.owner		= THIS_MODULE
};

static int __init char_init(void)
{
	//1 登记设备号
	if(major){
		devno = MKDEV(major,minor);
		register_chrdev_region(devno,1,"chardev");
	}else{
		alloc_chrdev_region(&devno,minor,1,"chardev");
	}
	return 0;
	//2 注册设备
	//初始化设备
	cdev_init(&test_cdev,&test_fops);
	//添加cdev到内核
	cdev_add(&test_cdev,&test_fops,1);

	printk("Hello kernel\n");
	return 0;
}

static void __exit char_exit(void)
{
	//1 从内核中删除cdev
	cdev_del(&test_cdev);
	//2 注销设备号
	unregister_chrdev_region(devno,1);

	printk("Good bye kernel\n");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Allan");

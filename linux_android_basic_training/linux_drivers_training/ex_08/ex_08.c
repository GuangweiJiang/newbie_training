#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <mach/gpio.h>
#include <mach/at91_pmc.h>
#include <mach/at91_pio.h>
#include <asm/uaccess.h>

#include <linux/spinlock.h>

#include "./test/gpio.h"

#undef __PDEBUG
//#define __PDEBUG

#ifdef __PDEBUG
#define printf(arg,x...) printk(KERN_ALERT "gpio debug:"arg,##x);
#else
#define printf(arg,x...)
#endif

struct gpiocdev{
		struct cdev dev;
		spinlock_t gpio_spinlock;
};


#define GPIO_MAJOR 0


struct class *my_class;
int gpio_major = GPIO_MAJOR;
struct gpiocdev *gpio_cdev;


int gpio_open(struct inode *inode,struct file *filp)
{
		return 0;
}

int gpio_release(struct inode *inode,struct file *filp)
{
		return 0;
}

int gpio_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
		return 0;
}

int gpio_read(struct file *filp,char __user *buf,size_t size,loff_t *ppos)
{
		return 0;
}


int gpio_ioctl(struct inode *inode,struct file *filp,unsigned int cmd,unsigned long arg)
{
		int ret=0;
		int temp;
		unsigned int temp0;
		unsigned long flags;
		unsigned int pio_addr;
		struct gpiostruct *gpio_struct;
		spin_lock_irqsave(&gpio_cdev->gpio_spinlock, flags);
		gpio_struct = kmalloc(sizeof(struct gpiostruct),GFP_KERNEL);
		if(!gpio_struct){
				printf("no mem\n");
				ret = -ENOMEM;
				goto exit1;
		}
		if(0!=copy_from_user(gpio_struct,(struct gpiostruct *)arg,sizeof(struct gpiostruct))){
				printf("copy mem fail!\n");
				ret = -ERESTARTSYS;
				goto exit0;
		}
		switch(gpio_struct->pio_group){
				case 'A':
						pio_addr = AT91_PIOA;
						break;
				case 'B':
						pio_addr = AT91_PIOB;
						break;
				case 'C':
						pio_addr = AT91_PIOC;
						break;
				default:
						printf("no vaid pio group!\n");
						ret = -EINVAL;
						goto exit0;
		}
		switch(cmd){
				case GPIO_CMD_SET_DIR:
						if(gpio_struct->dir){
								at91_sys_write(pio_addr + PIO_IDR,gpio_struct->pio_pin);
								at91_sys_write(pio_addr + PIO_PUDR,gpio_struct->pio_pin);
								at91_sys_write(pio_addr + (gpio_struct->value ? PIO_SODR : PIO_CODR),gpio_struct->pio_pin);
								at91_sys_write(pio_addr + PIO_OER,gpio_struct->pio_pin);
								at91_sys_write(pio_addr + PIO_PER,gpio_struct->pio_pin);
						}else{
								at91_sys_write(pio_addr + PIO_IDR,gpio_struct->pio_pin);
								at91_sys_write(pio_addr + (gpio_struct->value ? PIO_PUER : PIO_PUDR),gpio_struct->pio_pin);
								at91_sys_write(pio_addr + PIO_ODR,gpio_struct->pio_pin);
								at91_sys_write(pio_addr + PIO_PER,gpio_struct->pio_pin);
						}
						break;
				case GPIO_CMD_SET_VALUE:
						at91_sys_write(pio_addr + (gpio_struct->value ? PIO_SODR : PIO_CODR),gpio_struct->pio_pin);
						break;
				case GPIO_CMD_GET_VALUE:
						temp0 = 0;
						for(temp=0;temp<32;temp++)
								temp0 += ((gpio_struct->pio_pin>>temp)&0x1);
						if(temp0!=0x1){
								printf("pio pin err!\n");
								ret = -EINVAL;
								goto exit0;
						}
						if(0==(at91_sys_read(pio_addr+PIO_PSR)&gpio_struct->pio_pin) || 0!=(at91_sys_read(pio_addr+PIO_OSR)&gpio_struct->pio_pin) ){
		
								printf("io is inactive or isn't set to input!\n");
								gpio_struct->value = -2;
						}else{
								if(0==(at91_sys_read(pio_addr+PIO_PDSR)))
										gpio_struct->value = 0;
								else
										gpio_struct->value = 1;
						}
						if(0!=copy_to_user((struct gpiostruct *)arg,gpio_struct,sizeof(struct gpiostruct)))
								ret = -ERESTART;
						break;
				default:
						ret = -EINVAL;
						break;
		}
exit0:
		kfree(gpio_struct);
exit1:
		spin_unlock_irqrestore(gpio_cdev->gpio_spinlock, flags);
		return ret;
}



struct file_operations gpio_ops={
		.owner = THIS_MODULE,
		.open = gpio_open,
		.release = gpio_release,
		.write = gpio_write,
		.read = gpio_read,
		.ioctl = gpio_ioctl,
};

int gpio_module_init(void)
{
		int ret;
		dev_t devno;
		if(gpio_major){
				devno = MKDEV(gpio_major,0);
				ret = register_chrdev_region(devno,1,"gpio");
				if(ret<0){
						printf("register fail!\r\n");
						goto exit0;
				}
		}else{
				ret = alloc_chrdev_region(&devno,0,1,"gpio");
				if(ret<0){
						printf("register fail!\r\n");
						goto exit0;
				}
				gpio_major = MAJOR(devno);
		}
		gpio_cdev = kmalloc(sizeof(struct gpiocdev),GFP_KERNEL);

		if(!gpio_cdev){
				ret = -ENOMEM;
				goto exit1;
		}

		memset(gpio_cdev,0,sizeof(struct gpiocdev));
		spin_lock_init(&gpio_cdev->gpio_spinlock);
		cdev_init(&gpio_cdev->dev,&gpio_ops);
		gpio_cdev->dev.owner = THIS_MODULE;
		ret = cdev_add(&gpio_cdev->dev,devno,1);
		if(ret<0){
				printf("cdev add fail!\r\n");
				goto exit2;
		}
		my_class = class_create(THIS_MODULE,"gpio");
		if(IS_ERR(my_class)){
				printf("class create fail!\r\n");
				goto exit3;
		}
		device_create(my_class,NULL,devno,NULL,"gpio");
		return 0;
exit3:
		cdev_del(&gpio_cdev->dev);
exit2:
		kfree(gpio_cdev);
exit1:
		unregister_chrdev_region(devno,1);
exit0:
		return -1;
}

void gpio_module_exit(void)
{
		dev_t devno=MKDEV(gpio_major,0);
		device_destroy(my_class,devno);
		class_destroy(my_class);
		cdev_del(&gpio_cdev->dev);
		kfree(gpio_cdev);
		unregister_chrdev_region(devno,1);
}

module_init(gpio_module_init);
module_exit(gpio_module_exit);


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("lusson");
MODULE_DESCRIPTION("simple gpio driver");

/*
 *	write a simple kernel module, make it, and insert/remove from system.
 */
#include <linux/init.h>
#include <linux/module.h>

static int __init hello_kernel_init(void)
{
	printk("<1>" "hello kernel\n");
	return 0;
}

static void __exit hello_kernel_exit(void)
{
	printk("<1>" "goodbye kernel\n");
}

module_init(hello_kernel_init);
module_exit(hello_kernel_exit);
MODULE_LICENSE("Dual BSD/GPL");

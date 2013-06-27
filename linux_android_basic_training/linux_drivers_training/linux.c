#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int hello_init(void)
{
	printk(KERN_ALERT "Hello world enter\n");
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_ALERT "Hello world exit\n");

}



module_init(hello_init);
module_exit(hello_exit);
MODULE_AUTHOR("Jerry Liu");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("A simple Hello World Module");
MODULE_ALIAS("a simplest module");

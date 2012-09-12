/*
 * file name: ex_01.c
 * purpose: a simple module
 * creator: Allan
 * creat time: 2012-09-12
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

//加载模块
static int hello_init(void)
{
	printk("<0>""welcom to you!\n");
	return 0;
}

//注销模块
static void hello_exit(void)
{
	printk("<0>""goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Allan xing");

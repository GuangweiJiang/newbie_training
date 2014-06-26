/*
 * Filename:
 *      hello_kernel.c
 *
 * Copyright (C) 2014 Wistron
 * All rights reserved.
 *
 * Description:
 *      This file is a kernel module.
 *
 * Author/Created Date:
 *      Longbin Li, <beangr@163.com> Jun25'14
 *
 * Modification History:
 * 
 * Note:
 *
 */

/* Include Files */
#include <linux/init.h>
#include <linux/module.h>


/* IMPLEMENTATION */
/* the entry function */
static int __init hellokernel_init(void)
{
	printk("%s:hello kernel\n", __FUNCTION__);
	return 0;
}

/* the exit function */
static void __exit hellokernel_exit(void)
{
	printk("%s:goodbye kernel\n", __FUNCTION__);
}

module_init(hellokernel_init);
module_exit(hellokernel_exit);
MODULE_LICENSE("GPL");


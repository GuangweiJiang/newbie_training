//==========================================
// Filename:
//      linux.c
//
// Copyright (C) 2013 Wistron
// All rights reserved.
//
// Description:
//      Write a simple kernel module, make it, and insert/remove from system.
//
// Author/Created Date:
//      Jerry Liu Jun.28th
//
//
//--------------------------------------------------------------------------------------
// Include File
//--------------------------------------------------------------------------------------
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
//
//
//-----------------------------------------------------------------
// LOAD  FUNCTIONS
//-----------------------------------------------------------------
static int hello_init(void)
{
	printk(KERN_ALERT "Hello world enter\n");
	return 0;
}
//
//
//-----------------------------------------------------------------
// UNINSTALL FUNCTIONS
//-----------------------------------------------------------------
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
//
//
//----------------------------------------------------------------------------
// Function:
// 			1.static int hello_init(void)
//			2.static void hello_exit(void)
// Description:
//			1.The function is used to load the module.
//			2.The function is used to uninstall the module.

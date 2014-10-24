//==========================================
// Filename:
// hello.c
//
// Description:
// This file is a simple drive
// 
// Author/Created Date:
// Jimmy Jiang, 6.20
//
// Modification History:
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
//-----------------------------------------------------------------
// INTERNAL FUNCTIONS
//-----------------------------------------------------------------
MODULE_LICENSE("Dual BSD/GPL");             //the MACROS show drive`s license
static int hello_init(viod)                 //Define a function named hello_init
{
	printk(KERN_INFO "hello.world\n");  //show a word 
	return 0;
}

static void hello_exit(void)                //Define a function named hello_exit
{
	printk(KERN_INFO "goodbye.world\n");//show a word
}
module_init(hello_init);                    //When the module is inserted,systm will 
                                            //read function named hello_init
module_exit(hello_exit);                    //When the module is inserted,systm will
                                            //read function named hello_exit

//----------------------------------------------------------------------------
// Function:
// The file is a simple drive.when I insert the modulet,system can show "hello.world".
// when remove the module,system can show "goodbye.world".

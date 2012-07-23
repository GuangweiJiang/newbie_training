Linux driver training material - exercise 03
by guangwei@Jan12'10

Targets:
Use "misc_register" to add a char device to kernel, and use "echo" to communicate with driver.
(use API such as misc_register, misc_deregister)

Test Enviroment:
	Ubuntu 8.04 or later.
	
Time required:
	2 days

Purpose:
1. It's another easier way to register a char device driver, 
	think about what's the difference with the way of "cdev_add", 
	and what're the advantage and disadvantage?
2. Dig into the "misc_register" in kernel source, and learn how it works.

Refer books:
	"Essential Linux Device Drivers", chapter 5 - "Character Drivers" (p160-166, "Misc Drivers")

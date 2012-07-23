Linux driver training material - exercise 02
by guangwei@Jan12'10

Targets:
Write a simple char device driver, include below 3 parts of functions,
1. make a node under /dev 
	(use API such as class_create, class_device_create/device_create, class_destroy, class_device_destry/device destroy)
2. add char device to kernel 
	(use API such as register_chrdev_region, unregister_chrdev_region, cdev_alloc, cdev_init, cdev_add, cdev_del)
3. support file operation functions (open, release, read, write, ioctl) 


Test Enviroment:
	Ubuntu 8.04 or later.

Time required:
	5 days

Purpose:
1. Learn the basic conception of char device driver.
2. Learn what's major and minor device number, and learn how to dynamically/manually allocate device number.
3. Learn how to make /dev node, and learn what's udev, and what are the difference between udev and devfs.
4. Learn how to add char device to kernel.
5. In Linux, every device is treated as file, learn how to use the file operation in device driver.
6. Use "echo" to communicate with device driver (echo "xxx" > /dev/yyy)

Refer books:
	"Linux device drivers(3rd Edition)", chapter 3 - "Char Drivers"
	"Essential LInux Device Drivers", chapter 5 - "Character Drivers"
	"Linux设备驱动开发详解", chapter 5.4 - "udev设备文件系统"


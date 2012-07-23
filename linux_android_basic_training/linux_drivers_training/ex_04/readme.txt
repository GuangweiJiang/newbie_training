Linux driver training material - exercise 04
by guangwei@Jan13'10

Targets:
Write a kernel driver and a test application, let them communicate via ioctl.
(APIs used in kernel driver: __put_user/copy_to_user, __get_user/copy_from_user)
(APIs used in test application: open, ioctl, close)

Test Enviroment:
	Ubuntu 8.04 or later.
	
Time required:
	2 days

Purpose:
1. Learn how to use ioctl in kernel driver and application.
2. Learn how to define the ioctl commands.
3. Learn how to exchange data between kernel and user space.

Refer book:
	"Linux Device Drivers(3rd Edition)", chapter 6 "Advanced Char Driver Operations"(P135-147, "ioctl")

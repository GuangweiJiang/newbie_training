Linux driver training material - exercise 06
by guangwei@Aug03'10

Targets:
Build a driver, which has below features,
Execute "while" loop, and caculate how much time it costs;
Try to use mdelay/msleep, and caculate the time again! 
(APIs used in kernel driver: jiffies/get_jiffies_64, HZ, time_after(_eq), time_before(_eq), mdelay/ndelay/udelay, msleep/msleep_interruptible/ssleep)

Test Enviroment:
	Ubuntu 8.04 or later.
	
Time required:
	1 day

Purpose:
1. Measuring time lapses and comparing times
2. Knowing the current time
3. Delaying operation for a specified amount of time

Refer book:
	"Linux Device Drivers(3rd Edition)", chapter 7 "Time, Delays, and Deferred Work" (Page 183-201)

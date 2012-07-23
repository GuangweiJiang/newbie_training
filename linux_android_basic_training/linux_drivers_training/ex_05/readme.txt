Linux driver training material - exercise 05
by guangwei@Aug03'10

Targets:
Based on exercise 04, use "Semaphores" to handle the potential risks on "concurrency and race conditions".
(For example, when 2 or more applications manipulate a device at the same time, it may cause the race.)
(APIs used in kernel driver: init_MUTEX, down, up)

Test Enviroment:
	Ubuntu 8.04 or later.
	
Time required:
	2 days

Purpose:
1. Learn in which conditions we should handle "concurrency and race"? And what cause it?
2. Learn the ways to avoid the "race", such Semaphores and Spinlocks.

Refer book:
	"Linux Device Drivers(3rd Edition)", chapter 5 "concurrency and race conditions"

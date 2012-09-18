Linux driver training material - exercise 07
by guangwei@Sep18'12

Targets:
	1. Be familiar with android emulator(or real android device, such as Bohai, t-lite).
	2. Build kernel image of goldfish(or real android device) and run it in the emulator(or real android device).
	3. Add your own kernel driver to the goldfish(or real android device).

Test Enviroment:
	android sdk 1.5 or 1.6

Time Required:
	3 days.

Purpose:
	1. Learn how to deploy the android SDK.
		You can get the android SDK from server,
		//10.42.92.17/sw_rd$/Projects/Android/sdk
	2. Learn to use the basic commander to create avd, create sd card, and use "adb" (adb shell, adb pull, adb push...).
	3. Learn how to build image of goldfish, please refer "how-to" below.
		Please read the "README" file in the kernel root directory carefully.
		Make sure you know how to configure and build kernel image.
	4. Add your own kernel driver to the goldfish, check if it creates the nodes sucessfully under /dev, and use "echo" to commnicate with your driver.

---------------
How-to make zImage for emulator(goldfish)

1. download the kernel codes for goldfish 
	http://android.git.kernel.org/?p=kernel/common.git;a=summary
   or get it from server,
	//10.42.92.17/sw_rd$/Projects/Android/linux-kernel/google_rel/goldfish_special/android-goldfish-2.6.27 
2. install the toolchain and add the install path to $PATH
	//10.42.92.17/sw_rd$/Projects/Android/tool-chain
3. un-tar the kernel, and enter the root directory of kernel folder.
4. generate the .config file.
	make ARCH=arm goldfish_defconfig
5. build the kenel image (zImage)
	make ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi-
6. load the kenel image you just built in the emulator.
	emulator -kernel arch/arm/boot/zImage -avd android_avd
notes:
	-show-kernel                   display kernel messages 
---------------
	

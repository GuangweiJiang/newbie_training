Linux driver training material - exercise 09
by guangwei@Jan25'10

Targets:
	Build an Android application to communicate with the device driver via ioctl (use SDK+NDK).

Test Enviroment:
	android sdk 1.5 or 1.6
	android ndk 1.5 or 1.6

Time Required:
	2 days.

Purpose:
	1. Learn how to use NDK to build JNI shared library.
		1.1 Get the NDK package(linux ver) from server
			10.42.92.17/sw_rd$/Projects/Android/ndk/android-ndk-1.5-r1/android-ndk-1.5_r1-linux-x86.zip
		1.2 Un-zip the NDK files.
		1.3 Edit build/host-setup.sh,
			Change the 1st line to "#!/bin/bash"
		1.4 Open terminal, go to the root dir of "android-ndk-1.5_r1", type "build/host-setup.sh" to configure your host enviroment.
		1.5 type "make APP=hello-jni -B" to verify your host enviroment is OK!
	2. Learn how to write the JNI project, you can refer the samples codes in NDK or ex_07 example.
		Before build ex_07, please do as following,
		2.1 go to the root dir of "android-ndk-1.5_r1", use simple symlinks to redirect paths to ex_07 project's storage location. For example:
			ln -s -t sources/samples/ /home/jgw/projects/temp/exercise/ex_07/jni/ex_07/
			ln -s -t apps/ /home/jgw/projects/temp/exercise/ex_07/jni/ex_07/
		2.2 build the ex_07 project
			make APP=ex_07 -B
		2.3 there will generate "libex_07.so" in the directory "jni/ex_07/libs/armeabi/"
	3. Learn the name rule of JNI functions
		3.1 The JNI function name will contain "activity name" + "class name" + "function name",
			for example, in the android application "ex07", the 3 names as below, then the JNI function name shuld be "Java_com_wistron_ex07_ex07_ex07Test"
				activity name: 	com.wistron.ex07
				class name:		ex07
				function name:	ex07Test
	4. Learn how to call the function in the JNI shared library, you can refer the samples codes in NDK or ex07 example.
		4.1 Create an empty android project, the activity name is "com.wistron.ex07"
		4.2 Copy the folder "libs" (in directory "jni/ex_07") to the root directory of new Android project 
		4.3 Refresh your project (press F5), you will find the "libs" has include in your project.
		4.4 Add the following states to your Activity, it will load the 'ex_07' library on application startup.
			Notes: the lib name doesn't contain the prefix "lib" and suffix ".lib".
			static {
        		System.loadLibrary("ex_07");
    		}
		4.5 Declare the JNI function in your projects, for example
			public native int ex07Test();
		
Refer documents:
	android-ndk-1.5_r1/docs/INSTALL.TXT 
	android-ndk-1.5_r1/docs/HOWTO.TXT


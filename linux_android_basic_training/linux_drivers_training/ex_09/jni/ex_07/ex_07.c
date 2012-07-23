/* file name: 	ex_07.c
 * purpose: 	it's jni native codes, it will be called by java. 
 *				in this sample codes, it will call ioctl.
 * author: 		guangwei jiang
 * create date: Jan21'10
 * notes:
 *
 * History:
 *
 */


/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#define EX04_IOCTL_MAGIC 'v'
#define EX04_IOCTL_TEST			_IO(EX04_IOCTL_MAGIC, 1000)
#define EX04_IOCTL_GET_VAL		_IOR(EX04_IOCTL_MAGIC , 1001, int)
#define EX04_IOCTL_SET_VAL		_IOW(EX04_IOCTL_MAGIC , 1002, int)


// call the ioctl - EX04_IOCTL_TEST
// notes: 
//		the rule of naming a function: 
//			"activity name" + "class name" + "function name"
//		in our example below,
//			activity name: 	com.wistron.ex07
//			class name:		ex07
//			function name:	ex07Test
JNIEXPORT jint Java_com_wistron_ex07_ex07_ex07Test(JNIEnv * env,   
  jobject obj) { 
    int rc = 0;
    int fd = -1;
    fd = open("/dev/ex04_dev", O_RDWR);
    if(fd < 0) {
        rc = -1;
    } else{
        rc = ioctl(fd, EX04_IOCTL_TEST);
        if (rc < 0) {
        }
        close(fd);
    }
    return (jint)rc;
} 


// set the test_val to ex04_dev
JNIEXPORT jint Java_com_wistron_ex07_ex07_ex07Set(JNIEnv * env,   
  jobject obj, jint test_val) { 
    int rc = 0;
    int fd = -1;

    fd = open("/dev/ex04_dev", O_RDWR);
    if(fd < 0) {
        rc = -1;
    } else{
        rc = ioctl(fd, EX04_IOCTL_SET_VAL, &test_val);
        if (rc < 0) {
        }
        close(fd);
    }
    return (jint)rc;
} 


// get the test_val from ex04_dev
JNIEXPORT jint Java_com_wistron_ex07_ex07_ex07Get(JNIEnv * env,   
  jobject obj) { 
    int rc = 0;
    int fd = -1;
	int test_val;

    fd = open("/dev/ex04_dev", O_RDWR);
    if(fd < 0) {
        rc = -1;
    } else{
        rc = ioctl(fd, EX04_IOCTL_GET_VAL, &test_val);
        if (rc < 0) {
        }
        close(fd);
    }
    return (jint)test_val;
} 









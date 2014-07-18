#! /bin/bash
clear
gcc linklist.c user_test.c -o ll_test.o && echo "gcc ok"
if [ $? ]
then 
	read -p "press <ENTER> to excute test."
	echo "--------------------------------"
	./ll_test.o
fi

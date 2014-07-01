#! /bin/bash
make clean
make
gcc -o user.o user.c
#clear
echo "**make OK**"
file=`ls *.ko`
echo "	Press <ENTER> to insert $file module"
read
sudo insmod $file && echo "#insmod $file"
echo 'cat /proc/devices | grep "scull"' && cat /proc/devices | grep 'scull'
sudo chmod 666 /dev/scull0
ls -l /dev/scull*
echo "	Press <ENTER> to remove $file module"
read
sudo rmmod $file && echo "#rmmod $file"
echo "	Press <ENTER> to continue"
read
sudo dmesg

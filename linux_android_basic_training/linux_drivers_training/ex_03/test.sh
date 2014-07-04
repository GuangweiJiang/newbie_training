#! /bin/bash
make clean
make
gcc -o user.o user.c
#clear
echo "**make OK**"
file=`ls *.ko`
read -p"	Press <ENTER> to insert $file module"
sudo insmod $file && echo "#insmod $file"
echo '#cat /proc/devices | grep "misc"' && cat /proc/devices | grep 'misc'
echo '#sudo chmod 666 /dev/misc_dev0' && sudo chmod 666 /dev/misc_dev0
ls -l /dev/misc_dev*
echo '#echo "test" > /dev/misc_dev0' && echo "test" > /dev/misc_dev0
echo '#cat /dev/misc_dev0' && cat /dev/misc_dev0
echo '----------------------'
./user.o
echo '----------------------'
read -p "	Press <ENTER> to remove $file module"
sudo rmmod $file && echo "#rmmod $file"
read -p "	Press <ENTER> to continue"
sudo dmesg

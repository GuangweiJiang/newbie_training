#! /bin/bash
make clean
make
gcc -o user.o user.c
#clear
echo "**make OK**"
file=`ls *.ko`
read -p "	Press <ENTER> to insert $file module"
echo "#sudo insmod $file" && sudo insmod $file
echo '#cat /proc/devices | grep "scull"' && cat /proc/devices | grep 'scull'
echo '#sudo chmod 666 /dev/scull0' && sudo chmod 666 /dev/scull0
ls -l /dev/scull*
#echo '#echo "test" > /dev/scull0' && echo "test" > /dev/scull0
#echo '#cat /dev/scull0' && cat /dev/scull0
echo '------------./user.o-------------'
./user.o 
echo '---------------------------------'
read -p "	Press <ENTER> to remove $file module"
echo '#sudo rmmod $file' && sudo rmmod $file
read -p "	Press <ENTER> to continue"
sudo dmesg

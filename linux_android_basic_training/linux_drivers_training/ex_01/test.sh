#! /bin/bash
make
clear
echo "make OK"
file=`ls *.ko`
sudo insmod $file && echo "insmod $file"
sudo rmmod $file && echo "rmmod $file"
echo "Press <ENTER> to continue"
read
sudo dmesg

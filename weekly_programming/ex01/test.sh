#! /bin/bash
gcc sort.c -o sort.o
gcc generate.c -o generate.o
echo "gcc ok"
read -p "Generate source datas. yes or no ? <y/n>" select
if [ "$select" == "y" ]
then
	./generate.o
fi
read -p "press <ENTER> to excute sort."
./sort.o


#!/bin/bash
make clean
make

echo "---------btest---------"
./btest
echo -e "-----------------------\n"

echo "----------dlc----------"
./dlc -e bits.c
echo "-----------------------"

#!/bin/bash
make clean
make
echo "----------dlc----------"
./dlc -e bits.c
echo -e "-----------------------\n"
echo "---------btest---------"
./btest
echo -e "-----------------------\n"
echo "-------check.pl--------"
./bddcheck/check.pl 
echo -e "-----------------------\n"


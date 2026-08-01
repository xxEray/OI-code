#!/bin/bash

g++ bf.cpp -o bf.exe -O2
g++ gen.cpp -o gen.exe -O2
g++ ../string.cpp -o string.exe -O2

while $true ; do
	./gen.exe $RANDOM > string.in
	./bf.exe < string.in > string.ans
	./string.exe
	if diff -w string.out string.ans ; then
		echo AC
	else
		echo WA
		break
	fi
done

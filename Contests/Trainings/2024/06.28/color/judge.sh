#!/bin/bash

g++ bf.cpp -o bf.exe -O2
g++ gen.cpp -o gen.exe -O2
g++ ../color.cpp -o color.exe -O2

while $true ; do
	./gen.exe $RANDOM > color.in
	./bf.exe < color.in > color.ans
	./color.exe
	if diff -w color.out color.ans ; then
		echo AC
	else
		echo WA
		break
	fi
done

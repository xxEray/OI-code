#!/bin/bash

g++ bf.cpp -o bf.exe -O2
g++ gen.cpp -o gen.exe -O2
g++ ../per.cpp -o per.exe -O2

while $true ; do
	./gen.exe $RANDOM > per.in
	./std.exe < per.in > per.ans
	./per.exe
	if diff -w per.out per.ans ; then
		echo AC
	else
		echo WA
		break
	fi
done

#!/bin/bash

g++ bf.cpp -o bf.exe -O2
g++ gen.cpp -o gen.exe -O2
g++ ../arcanaeden.cpp -o arcanaeden.exe -O2

while $true ; do
	./gen.exe $RANDOM > arcanaeden.in
	./bf.exe < arcanaeden.in > arcanaeden.ans
	./arcanaeden.exe
	if diff -w arcanaeden.out arcanaeden.ans ; then
		echo AC
	else
		echo WA
		break
	fi
done

#!/bin/bash

while $true ; do
	./gen.exe $RANDOM > gothic.in
	./std.exe < gothic.in > gothic.ans
	./gothic.exe < gothic.in > gothic.out
	if diff -w gothic.out gothic.ans ; then
		echo AC
	else
		echo WA
		break
	fi
done

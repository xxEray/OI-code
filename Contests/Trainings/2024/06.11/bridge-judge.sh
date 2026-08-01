#!/bin/bash

while $true ; do
	./bridge-gen.exe $RANDOM
	./bridge-std.exe
	./bridge.exe
	if diff bridge.out bridge.ans ; then
		echo AC
	else
		break
	fi
done

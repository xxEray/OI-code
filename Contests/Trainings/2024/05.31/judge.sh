#!/bin/bash

while $true ; do
	./tree-gen.exe $RANDOM
	./tree-lsl.exe
	./tree.exe
	if diff tree.out tree.ans ; then
		echo AC
	else
		break
	fi
done

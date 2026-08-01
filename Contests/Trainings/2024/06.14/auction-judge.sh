#!/bin/bash

while $true ; do
	./auction-gen.exe $RANDOM
	./auction-std.exe
	./auction.exe
	if diff auction.out auction.ans ; then
		echo AC
	else
		break
	fi
done

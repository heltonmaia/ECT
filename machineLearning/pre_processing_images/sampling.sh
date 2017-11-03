#!/bin/sh

path0="figures/"
path1="figuresSamples/"

#resample of 30
count=465
	while [ $count -lt 61113 ]
	do
		
		echo "image: $count"
		cp $path0${count}.jpg $path1${count}.jpg
		count=`expr $count + 30`
	done

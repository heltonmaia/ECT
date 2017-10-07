#!/bin/sh

path0="trackingFigures/"
path1="angleDraw/"

for i in `seq 30288 $max`
	do
  		echo "output: $i"
  		./overlay $path0${i}.jpg $path1${i}.jpg
	done

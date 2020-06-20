#!/bin/bash

rm -rf out/
mkdir out
qcc couette.c -O2 -lm -o out/couette
cd out
./couette > speed.ppm 2>flow.log
tail -n1 speed.ppm
#display speed.ppm
animate speed.ppm

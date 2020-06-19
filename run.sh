#!/bin/bash

rm -rf out/
mkdir out
qcc couette_.c -O2 -lm -o out/couette
cd out
./couette > speed.ppm
display speed.ppm

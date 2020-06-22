#!/bin/bash

rm -rf out/
mkdir out
qcc couette.c -O2 -lm -o out/couette
qcc -Wall -O2 couette.c -o out/couette -L$BASILISK/gl -lglutils -lfb_glx -lGLU -lGLEW -lGL -lX11 -lm
cd out
./couette > speed.ppm 2>flow.log
tail -n1 speed.ppm
#display speed.ppm
animate speed.ppm

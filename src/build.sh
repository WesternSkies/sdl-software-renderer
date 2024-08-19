#!/bin/sh
gcc -g draw.c moremath.c draw3d.c main.c -lm -lSDL2 -pthread

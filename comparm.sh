#!/bin/sh
arm-linux-gnueabi-gcc-11 -static $1.c -l SDL -o $1arm

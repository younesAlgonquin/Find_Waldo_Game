#!/bin/sh

#
# Installation: chmod +x ./make.sh
# Usage: ./make.sh
#

# shell variables: declare and assign value
GCC_OPTIONS="-g -ansi -pedantic -Wall"
TARGET1="find_waldo"



echo "gcc $GCC_OPTIONS $TARGET1.c -o $TARGET1"
gcc $GCC_OPTIONS $TARGET1.c -o $TARGET1



exit 0

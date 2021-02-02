#!/bin/sh

if [ ! -e bin/linux ]; then
    mkdir -p bin/linux || exit
fi
gcc -Wall -Wextra main.c tea.c -std=c99 -Wpedantic -o bin/linux/tea

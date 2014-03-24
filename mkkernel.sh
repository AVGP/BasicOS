#!/bin/bash

mkdir bin
nasm boot/bootloader.asm -f bin -o bin/bootloader.bin
gcc -ffreestanding -c kernel.c -o bin/kernel.o

ld -Ttext 0x1000 --oformat binary -o bin/kernel.bin bin/kernel.o
cat bin/bootloader.bin bin/kernel.bin > kernel.img

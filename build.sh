#!/bin/bash

set -e
set -x

# Create build directory if not exists
mkdir -p build

# Assemble bootloader and PM code
nasm -f bin src/boot.asm -o build/boot.bin
nasm -f elf src/pm.asm -o build/pm.o

# Compile all .c files automatically
OBJS=""
for file in src/*.c; do
    filename=$(basename "$file" .c)
    gcc -m32 -ffreestanding -c "$file" -o "build/$filename.o"
    OBJS="$OBJS build/$filename.o"
done

# Link all .o files
ld -m elf_i386 -T src/linker.ld -nostdlib build/pm.o $OBJS -o build/kernel.elf

# Convert ELF to binary
objcopy -O binary build/kernel.elf build/kernel.bin

# Combine bootloader and kernel binary
cat build/boot.bin build/kernel.bin > os-image.bin

# Run in QEMU
qemu-system-i386 -vga std -fda os-image.bin

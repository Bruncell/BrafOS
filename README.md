# BrafOS

BrafOS is an ARM system written in C, assembler.  
It uses a framebuffer to draw pixels, letters.

## BUILD
In order to compile and assemble brafos you need to enter:
```
make
```

After successful build, you can run the system in QEMU using either of the following commands:

```
qemu-system-i386 -vga std -fda build/os-image.bin
```
or
```
qemu-system-i386 -vga std -fda build/os-image.img
```
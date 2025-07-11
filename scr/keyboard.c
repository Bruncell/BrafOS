#include "keyboard.h"
#include <stdint.h>

static inline uint8_t inb(uint16_t port) 
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}



char read_scancode() 
{
    while ((inb(0x64) & 1) == 0);
    return inb(0x60);
}




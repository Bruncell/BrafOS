#include "keyboard.h"
#include "graphic.h"
#include <stdint.h>


static char ascii_[256];

void init_ascii() 
{
    ascii_[0x0E] = '\b';
    ascii_[0x8E] = 0;
    ascii_[0x0F] = '\t';
    ascii_[0x10] = 'q';
    ascii_[0x11] = 'w';
    ascii_[0x12] = 'e';
    ascii_[0x13] = 'r';
    ascii_[0x14] = 't';
    ascii_[0x15] = 'y';
    ascii_[0x16] = 'u';
    ascii_[0x17] = 'i';
    ascii_[0x18] = 'o';
    ascii_[0x19] = 'p';
    ascii_[0x1E] = 'a';
    ascii_[0x1F] = 's';
    ascii_[0x20] = 'd';
    ascii_[0x21] = 'f';
    ascii_[0x22] = 'g';
    ascii_[0x23] = 'h';
    ascii_[0x24] = 'j';
    ascii_[0x25] = 'k';
    ascii_[0x26] = 'l';
    ascii_[0x2B] = '$';
    ascii_[0x2C] = 'z';
    ascii_[0x2D] = 'x';
    ascii_[0x2E] = 'c';
    ascii_[0x2F] = 'v';
    ascii_[0x30] = 'b';
    ascii_[0x31] = 'n';
    ascii_[0x32] = 'm';
    ascii_[0x39] = ' ';
    ascii_[0x35] = '/';
    ascii_[0x1C] = 0x0D;

}




static inline uint8_t inb(uint16_t port) 
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

char read_scancode() 
{
    while ((inb(0x64) & 1) == 0)
    {
    	
    }
    return inb(0x60);
}

char ReadKey()
{

char ScanCode = read_scancode();
char AsciiCode = ascii_[ScanCode];
return AsciiCode;


}

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

#define INPUTBUFFER_SIZE 32

#define PITCH (*(uint16_t*) 0x7010)
#define WIDTH (*(uint16_t*) 0x7012)
#define HEIGHT (*(uint16_t*) 0x7014)
#define BPP (*(uint8_t*) 0x7019)
#define FRAMEBUFFER (*(uint32_t*) 0x7028)

#endif

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

#define PITCH (*(uint16_t*) 0x9010)
#define WIDTH (*(uint16_t*) 0x9012)
#define HEIGHT (*(uint16_t*) 0x9014)
#define BPP (*(uint8_t*) 0x9019)
#define FRAMEBUFFER (*(uint32_t*) 0x9028)

#endif

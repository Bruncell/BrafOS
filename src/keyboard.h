#include <stdint.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

extern char ascii[256];

static inline uint8_t inb(uint16_t port);
char read_scancode();
uint8_t ReadKey();


#endif

#include <stdint.h>

#ifndef KEYBOARD_H
#define KEYBOARD_H

static inline uint8_t inb(uint16_t port);
char read_scancode();


#endif

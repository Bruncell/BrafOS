#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <stdint.h>

void pix(int x, int y, uint32_t color);
void DrawLetter(int x, int y, uint32_t FrontColor, uint32_t BackColor, int LetterID);

static inline uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b)
{
return ((r & 0x1F) << 10) | ((g & 0x1F) << 5) | (b & 0x1F);
}

#endif

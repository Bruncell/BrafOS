#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <stdint.h>

void pix(int x, int y, uint32_t color);
void DrawLetter(int x, int y, uint32_t FrontColor, uint32_t BackColor, uint8_t LetterID);
void Print(int CursorX, int CursorY, uint32_t FrontColor, uint32_t BackColor, const char *word);
uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b);

#endif

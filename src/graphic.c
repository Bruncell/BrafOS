#include "font.h"
#include "graphic.h"
#include "consts.h"




void pix(int x, int y, uint32_t color) 
{

    uint16_t* fb = (uint16_t*)FRAMEBUFFER;
    fb[y * (PITCH / 2) + x] = color;
}

void DrawLetter(int x, int y, uint32_t FrontColor, uint32_t BackColor, int LetterID)
{

x *= 8;
y *=10;

int temp_x = x;
	
 for(int i = 0; i < 10; i++)
 {
 	  uint8_t bits = font[LetterID][i];
	  for(int j = 0; j < 8; j++)
 	  {
 	  uint8_t bit = (bits >> (7 - j)) & 1;
	  uint32_t color = bit ? FrontColor : BackColor;
 	  pix(x, y, color);
	  x++;	
	  }
	  x = temp_x;
	  y++;

 }
}


#include "font.h"
#include "graphic.h"
#include "consts.h"
#include "keyboard.h"

uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((r & 0x1F) << 10) | ((g & 0x1F) << 5) | (b & 0x1F);
}

void pix(int x, int y, uint32_t color) 
{

    uint16_t* fb = (uint16_t*)FRAMEBUFFER;
    fb[y * (PITCH / 2) + x] = color;
}

void DrawLetter(int CursoX, int CursoY, uint32_t FrontColor, uint32_t BackColor, uint8_t LetterID)
{

CursoX *= 8;    // Font 8x10
CursoY *=10;

int temp_x = CursoX;

	for(int i = 0; i < 10; i++)
	{
		uint8_t bits = font[LetterID][i];
		 
	for(int j = 0; j < 8; j++)
 	{				
	uint8_t bit = (bits >> (7 - j)) & 1;
	uint32_t color = bit ? FrontColor : BackColor;
						
	pix(CursoX, CursoY, color);
  				 	 
  				 	    
	CursoX++;	
	}
	CursoX = temp_x;
	CursoY++;
	}
}


void Print(int CursorX, int CursorY, uint32_t FrontColor, uint32_t BackColor, char word[100])
{
int i = 0;
while(word[i] != 0)
{

DrawLetter(CursorX, CursorY, FrontColor, BackColor, word[i]);

CursorX++; 

if (CursorX >= WIDTH / 8) 
{
CursorX = 0;
CursorY++;
}
	
i++;

}
	
}


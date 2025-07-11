#include <stdint.h>
#include "graphic.h"
#include "font.h"
#include "consts.h"
#include "keyboard.h"


void main() 
{



int CursorX = 0;
int CursorY = 0;

uint16_t color = rgb555(0, 0, 200);


while(1)
{

	uint8_t KeyCode = ReadKey();
	if(KeyCode == 0)
	continue;

   
	DrawLetter(CursorX, CursorY, 0xFFFF, color, KeyCode);
	CursorX++;
	
	if (CursorX >= WIDTH / 8) 
	{
	CursorX = 0;
	CursorY++;
	}
            
}

while(1);

}

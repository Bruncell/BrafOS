#include "global.h"
#include "consts.h"
#include "graphic.h"
#include "keyboard.h"



int WriteConsol()
{

	char KeyCode = ReadKey();

	if(KeyCode == 0)
	return 1;

	if(KeyCode == 0x08 && InputLength != 0 && InputBuffer[0] != 0)
	{

    InputLength--;
    InputBuffer[InputLength] = 0;
	CursorX--;
 	DrawLetter(CursorX, CursorY, font_color, background_color, 0);
   
	return 1;
	}

	
	
	if(KeyCode == 0x0D)
    {
	Print(1, 2, font_color, background_color, "                  ");
	Print(1, 2, font_color, background_color, InputBuffer);
	
	return 1;
	}

	if(KeyCode != 0x08)
	{

	if (InputLength < INPUTBUFFER_SIZE - 1) 
	{
	
	InputBuffer[InputLength] = KeyCode;
	InputLength++;
	InputBuffer[InputLength] = '\0';
	
	}

	DrawLetter(CursorX, CursorY, font_color, background_color, KeyCode);
	CursorX++;
	
	if (CursorX >= WIDTH / 8) //font 8x10
	{
	
	CursorX = 0;
	CursorY++;
	
	}
	}

	return 0;

}
void ClearConsol()
{
	
}

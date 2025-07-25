#include "global.h"
#include "consts.h"
#include "graphic.h"
#include "keyboard.h"
#include "consol.h"
#include "nodes.h"





void __stack_chk_fail_local(void) 
{
 
    while(1) {}
}



void ClearScreen()
{


for(int i = 0; i < HEIGHT; i++)
{
	for(int j = 0; j < WIDTH; j++)
	{
		pix(j, i, background_color);
	}
}
}


int WriteConsol()
{
Print(1, 1, user_color, background_color, user);


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

	CutTokens();
	
	return 1;
	}

	if(KeyCode != 0x08)
	{

	if (InputLength < INPUTBUFFER_SIZE - 2) 
	{
	
	InputBuffer[InputLength] = KeyCode;
	InputLength++;
	InputBuffer[InputLength] = '\0';
	
	}
	else
	{
		while (InputLength > 0)
		{
   		  InputLength--;
  		  CursorX--;
  		  DrawLetter(CursorX, CursorY, font_color, background_color, ' ');
   		  InputBuffer[InputLength] = '\0';
		}
		return 1;

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

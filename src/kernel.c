#include <stdint.h>
#include "global.h"
#include "consts.h"
#include "font.h"
#include "graphic.h"
#include "keyboard.h"
#include "consol.h"



void main() 
{

init_ascii();

    table_background_color = rgb555(0, 0, 200);
    background_color = rgb555(1, 1, 1);
    font_color = rgb555(250, 250, 250);
    user_color = rgb555(0, 250, 0);



for(int i = 0; i < 400; i++)
{
	for(int j = 0; j < 640; j++)
	{
		pix(j, i, background_color);
	}
}

Print(1, 1, user_color, background_color, user);


while(1)
{

WriteConsol();
      
}

while(1);

}

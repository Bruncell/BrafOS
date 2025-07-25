#include <stdint.h>
#include "global.h"
#include "consts.h"
#include "graphic.h"
#include "keyboard.h"
#include "consol.h"




void main() 
{




    table_background_color = rgb555(0, 0, 200);
    background_color = rgb555(1, 1, 1);
    font_color = rgb555(250, 250, 250);
    font_color_red = rgb555(250, 0,0);
    font_color_blue = rgb555(0, 50, 240);
    font_color_green = rgb555(0, 250, 0);
    user_color = rgb555(0, 250, 0);



for(int i = 0; i < HEIGHT; i++)
{
	for(int j = 0; j < WIDTH; j++)
	{
		pix(j, i, background_color);
	}
}




while(1)
{

WriteConsol();
      
}

while(1);

}

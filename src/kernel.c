#include <stdint.h>
#include "graphic.h"
#include "font.h"
#include "consts.h"
#include "keyboard.h"


void main() 
{



int CursorX = 0;
int CursorY = 0;




while(1)
{

uint8_t scancode = read_scancode();


     if (scancode & 0x80)
              continue;

          
uint16_t color = rgb555(0, 0, 200);
          
              DrawLetter(CursorX, CursorY, 0xFFFF, color, scancode);
                CursorX++;
                if (CursorX >= WIDTH / 20) 
                {
                    CursorX = 0;
                    CursorY++;
                }
            
}

while(1);

}

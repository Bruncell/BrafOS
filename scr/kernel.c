#include <stdint.h>



#define PITCH 				 (*(uint16_t*) 0x9010)
#define WIDTH 				 (*(uint16_t*) 0x9012)
#define HEIGHT 				 (*(uint16_t*) 0x9014)
#define BPP 				 (*(uint8_t*)  0x9019)
#define FRAMEBUFFER 		 (*(uint32_t*) 0x9028)


uint8_t font[256][10] = 
{
    [0x1E] = { // a
        0b00000000,
        0b00000000,
        0b00000000,
        0b01111000,
        0b10000100,
        0b00000100,
        0b01111100,
        0b10000100,
        0b10000100,
        0b01111010,
    },

    [0x30] = { // b
        0b00000000,
        0b00000000,
        0b11000000,
        0b01000000,
        0b01000000,
        0b01011100,
        0b01100010,
        0b01000010,
        0b01100010,
        0b11011100,
    },

    [0x2E] = { // c
        0b00000000,
        0b00000000,
        0b00000000,
        0b00111000,
        0b01000100,
        0b10000000,
        0b10000000,
        0b10000000,
        0b01000100,
        0b00111000,
    },

    [0x26] = { // l
        0b00000000,
        0b00000000,
        0b01110000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b01111100,
    },

    [0x12] = { // e
        0b00000000,
        0b00000000,
        0b00000000,
        0b01111000,
        0b10000100,
        0b10000100,
        0b11111100,
        0b10000000,
        0b10000100,
        0b01111000,
    },

    [0x13] = { // r
        0b00000000,
        0b00000000,
        0b00000000,
        0b01101100,
        0b00110010,
        0b00100000,
        0b00100000,
        0b00100000,
        0b00100000,
        0b01111000,
    },

    [0x23] = { // h
        0b00000000,
        0b00000000,
        0b11100000,
        0b01000000,
        0b01000000,
        0b01011000,
        0b01100100,
        0b01000100,
        0b01000100,
        0b11101110,
    },

    [0x18] = { // o
         0b00000000,
         0b00000000,
         0b00000000,
         0b01111000,
         0b10000100,
         0b10000100,
         0b10000100,
         0b10000100,
         0b10000100,
         0b01111000,
     },

     [0x19] = { // p
          0b00000000,
          0b00000000,
          0b00000000,
          0b11011100,
          0b01100010,
          0b01100010,
          0b01011100,
          0b01000000,
          0b01000000,
          0b11100000,
      },

      [0x35] = { // p
           0b00000110,
           0b00001100,
           0b00001000,
           0b00011000,
           0b00010000,
           0b00110000,
           0b01100000,
           0b01000000,
           0b11000000,
           0b10000000,
       },

};
//////////////////////////////

/*/uint8_t key_to_letterID[128] = {
    [0x1E] = 1, // 'A'
    [0x30] = 2, // 'B'
    [0x2E] = 3, // 'C'
    [0x20] = 4, // 'D'
    [0x12] = 5, // 'E'
    [0x21] = 6, // 'F'
    [0x22] = 7, // 'G'
    [0x23] = 8, // 'H'
    [0x17] = 9, // 'I'
    [0x24] = 10, // 'J'
    [0x25] = 11, // 'K'
    [0x26] = 12, // 'L'
    [0x32] = 13, // 'M'
    [0x31] = 14, // 'N'
    [0x18] = 15, // 'O'
    [0x19] = 16, // 'P'
    [0x10] = 17, // 'Q'
    [0x13] = 18, // 'R'
    [0x1F] = 19, // 'S'
    [0x14] = 20, // 'T'
    [0x16] = 21, // 'U'
    [0x2F] = 22, // 'V'
    [0x11] = 23, // 'W'
    [0x2D] = 24, // 'X'
    [0x15] = 25, // 'Y'
    [0x2C] = 26  // 'Z'
};/*/

/*/uint8_t ascii_to_scancode[128] = {
    ['a'] = 0x1E,
    ['b'] = 0x30,
    ['c'] = 0x2E,
    ['d'] = 0x20,
    ['e'] = 0x12,
    ['f'] = 0x21,
    ['g'] = 0x22,
    ['h'] = 0x23,
    ['i'] = 0x17,
    ['j'] = 0x24,
    ['k'] = 0x25,
    ['l'] = 0x26,
    ['m'] = 0x32,
    ['n'] = 0x31,
    ['o'] = 0x18,
    ['p'] = 0x19,
    ['q'] = 0x10,
    ['r'] = 0x13,
    ['s'] = 0x1F,
    ['t'] = 0x14,
    ['u'] = 0x16,
    ['v'] = 0x2F,
    ['w'] = 0x11,
    ['x'] = 0x2D,
    ['y'] = 0x15,
    ['z'] = 0x2C,
};/*/




static inline uint8_t inb(uint16_t port) 
{
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((r & 0x1F) << 10) | ((g & 0x1F) << 5) | (b & 0x1F);
}

char read_scancode() 
{
    while ((inb(0x64) & 1) == 0);
    return inb(0x60);
}


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




void main() 
{



uint16_t green = rgb555(0, 255, 0);

int CursorX = 0;
int CursorY = 0;




while(1)
{

uint8_t scancode = read_scancode();


     if (scancode & 0x80)
              continue;

          

          
              DrawLetter(CursorX, CursorY, 0xFFFF, 0x0000, scancode);
                CursorX++;
                if (CursorX >= WIDTH / 20) 
                {
                    CursorX = 0;
                    CursorY++;
                }
            
}

while(1);

}

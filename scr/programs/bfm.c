#include "bfs.h"
#include "bfm.h"

#include "../keyboard.h"
#include "../consol.h"
#include "../nodes.h"
#include "../global.h"
#include "../consts.h"
#include "../graphic.h"

static char FileName[9];
static char FileExt[4];

static char FileName_f[9];
static char FileExt_f[4];

static char buffer[ROOT_DIR_SECTORS * 512];

#define MAX_SECTORS 16
#define SECTOR_SIZE 512

static char filetext[MAX_SECTORS * SECTOR_SIZE];



int calc_offset(int cursorX, int cursorY) 
{
    int logical_index = cursorY * 80 + cursorX;

    int full_sectors = logical_index / 508;
    int rest = logical_index % 508;

    return full_sectors * 512 + 4 + rest;
}



void BrafTextEditor(const char *file)
{


    for (int i = 0; i < ROOT_DIR_SECTORS; i++)
    {
        ReadSector(ROOT_DIR_LBA + i, buffer + (i * 512));
    }
    




int name_len = 0;
while(file[name_len] != '.' && file[name_len] != '\0' && name_len < 8) 
{
    FileName[name_len] = file[name_len];
    name_len++;
}
FileName[name_len] = '\0';

int ext_len = 0;
if (file[name_len] == '.') 
{
    name_len++;
    while(file[name_len + ext_len] != '\0' && ext_len < 4) 
    {
        FileExt[ext_len] = file[name_len + ext_len];
        ext_len++;
    }
}
FileExt[ext_len] = '\0';







    for (int i = 0; i < ROOT_DIR_SIZE; i += 16)
    {
        if (buffer[i] == 0)
        continue;


int filenamelength = 0;
         
            for (int j = 0; j < 8; j++)
            {
            if(buffer[i + j] != 0)
           	   filenamelength++;
           	   
               FileName_f[j] = buffer[i + j];
            }
            FileName_f[9] = '\0';
		
            for (int j = 8; j < 11; j++)
            {
               FileExt_f[j - 8] =  buffer[i + j];
            }
            FileExt_f[11] = '\0';






         
			if(strcmp(FileName_f, FileName) == 0 && strcmp(FileExt_f, FileExt) == 0)
			{

				for(int i = 0; i < HEIGHT; i++)
				{
					for(int j = 0; j < WIDTH; j++)
					{
						pix(j, i, background_color);
					}
				}





				uint32_t sector =
				
   					 ((uint32_t)buffer[i + 11]) |
   					 ((uint32_t)buffer[i + 12] << 8) |
   					 ((uint32_t)buffer[i + 13] << 16) |
  			 	     ((uint32_t)buffer[i + 14] << 24);





  			int size = buffer[i + 15];

  			if(size > 7)
  			{
  			Print(0 ,4,font_color_red, background_color, "file too big!");
  			return;
  			}


			int CursorX = 0;
			int CursorY = 0;

			int ctrl = 0;


			uint32_t next = sector;
			
			for (int i = 0; i < size; i++) 
			{
			    ReadSector(next, filetext + i * 512);

			    
			
			    next = ((uint32_t)filetext[i * 512 + 0]) |
			           ((uint32_t)filetext[i * 512 + 1] << 8) |
			           ((uint32_t)filetext[i * 512 + 2] << 16) |
			           ((uint32_t)filetext[i * 512 + 3] << 24);
			}
			

/////////////////////////////////////////////////		

for(int y = 45 * 10; y < HEIGHT; y++)
	for(int j = 0; j < WIDTH; j++)
     pix(j, y, 0x00F);	

     char size_char[5];
     int_to_str(size * 512, size_char);

	 Print(35 ,46,0xFFFF, 0x00F, "(ctrl + w) - to save, (ctrl + c) - to exit");

     Print(0 ,46,0xFFFF, 0x00F, FileName_f);
     Print(filenamelength ,46,0xFFFF, 0x00F, ".");
     Print(filenamelength + 1 ,46,0xFFFF, 0x00F, FileExt_f);
     Print(filenamelength + 5 ,46,0xFFFF, 0x00F, "size: ");
     Print(filenamelength + 10,46,0xFFFF, 0x00F, size_char);
     Print(filenamelength + 16,46,0xFFFF, 0x00F, "bytes");
     
  			 	     
while(1)
{

			


			
uint8_t scancode = read_scancode();
						
					
	if(scancode == 0x9D)			
	ctrl = 0;
			
	if(scancode == 0x1D)			
	ctrl = 1;
			
	if(ctrl == 1 && scancode == 0x2E)
	{
	ClearScreen();
	return;			
	}

	if (ctrl == 1 && scancode == 0x11) 
	{
	next = sector;
	
	for (int i = 0; i < size; i++) 
	{
	WriteSector(next, filetext + i * 512, 512);

	next = ((uint32_t)filetext[i * 512 + 0]) |
	((uint32_t)filetext[i * 512 + 1] << 8) |
	((uint32_t)filetext[i * 512 + 2] << 16) |
	((uint32_t)filetext[i * 512 + 3] << 24);
	}

	Print(0 ,45,font_color, 0x00F, "                    ");
	Print(0, 45, font_color_green, 0x00F, "file was saved!");
	
	continue;
	
	}
			
	if(scancode == 0x4D && CursorX != 79 && calc_offset(CursorX+1, CursorY) < 512 * size)
	CursorX++;
			
	if(scancode == 0x4B && CursorX != 0 && calc_offset(CursorX-1, CursorY) < 512 * size)
	CursorX--;
			
	if(scancode == 0x48 && CursorY != 0 && calc_offset(CursorX, CursorY-1) < 512 * size)
	CursorY--;		
			
	if(scancode == 0x50 && CursorY != 100 && calc_offset(CursorX, CursorY+1) < 512 * size)
	CursorY++;	


	int x = 0, y = 0;
    for(int i = 0; i < 512 * size; i++)
	{


    if ((i % 512) < 4)
    continue;
        
	if(CursorX == x && CursorY == y)
	{
	DrawLetter(CursorX, CursorY,  background_color, font_color, filetext[i]);
	}
	else
	{
	DrawLetter(x, y, font_color, background_color, filetext[i]);
	}

	x++;
	
	if(x == 80)
	{
	y++;
	x = 0;
	}
	
	}
			

	char KeyCode = scancode_to_ascii(scancode);
	if(KeyCode == 0)
	continue;


 	if (KeyCode >= 32 && KeyCode <= 126) 
 	{
        int offset = calc_offset(CursorX, CursorY);
        

    if (offset < size * 512 && (offset % 512) >= 4) 
	{
    filetext[offset] = KeyCode;
    CursorX++;
    Print(0 ,45,font_color_red, 0x00F, "             ");	
            
    if (CursorX == 80) 
    {
    CursorX = 0;
    CursorY++;
    }
    
	}
	else
	{
	Print(0 ,45,font_color_red, 0x00F, "file is full!");	
	}
	}



    

		


}		 
}   	
}
    
    Print(0 ,4,font_color_red, background_color, " no such file in derectory!");


}


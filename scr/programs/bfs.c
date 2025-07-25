#include "bfs.h"
#include "../nodes.h"
#include "../global.h"
#include "../consts.h"
#include "../graphic.h"

#define ATA_DATA         0x1F0
#define ATA_ERROR        0x1F1
#define ATA_SECTOR_COUNT 0x1F2
#define ATA_LBA_LOW      0x1F3
#define ATA_LBA_MID      0x1F4
#define ATA_LBA_HIGH     0x1F5
#define ATA_DRIVE_HEAD   0x1F6
#define ATA_STATUS       0x1F7
#define ATA_COMMAND      0x1F7

#define BITMAP_SECTOR 72
#define MAX_SECTORS 4096

uint8_t bitmap[512];

static uint8_t buffer[ROOT_DIR_SIZE];

static const char hex_chars[17] = "0123456789abcdef";


void PrintHex(unsigned char byte, int y, int x)
{

	char hex_str[3];



hex_str[0] = hex_chars[(byte >> 4) & 0x0F];
hex_str[1] = hex_chars[byte & 0x0F];
hex_str[2] = '\0';

Print(x, y, font_color_blue, background_color, "0x");
Print(x+2, y, font_color_blue, background_color, hex_str);

}

static int ata_wait()
{
int y = 10;

int timeout = 100000;
unsigned char status;

	while (timeout > 0) 
	{
	    status = inb(ATA_STATUS);

	    if (!(status & 0x80))
	    {
	     break;	
	    }
	    timeout--;

	}


	
	if (timeout <= 0) 
	{
	    return 0;
	}
	
	if (status & 0x01) 
	{
	    return 0;
	}

	timeout = 100000;
	 
    while (timeout > 0) 
    {
        status = inb(ATA_STATUS);

        
        if (status & 0x08)
        {

            break;
        }
        if (status & 0x01) 
        {
            return 0;
        }
        timeout--;
   	}

   	
   	    if (timeout <= 0) 
  	    {

           return 0;
  	    }



    return 1;
}

void set_bit(int bit) 
{
    bitmap[bit / 8] |= (1 << (bit % 8));
}

bool is_bit_free(int bit) 
{
    return !(bitmap[bit / 8] & (1 << (bit % 8)));
}



uint32_t AllocateFileSectors(uint8_t size) 
{
    ReadSector(BITMAP_SECTOR, bitmap);

    uint32_t chain[256];
    int found = 0;

   
    for (int i = 0; i < MAX_SECTORS && found < size; i++) 
    {
        if (is_bit_free(i)) 
        {
            set_bit(i);
             WriteSector(BITMAP_SECTOR, bitmap, 512);
            
            chain[found++] = i + 73;
        }
    }

    if (found < size) 
    {
    while(1)
    {
    	
    }
    }

   
    

    
for (int i = 0; i < size; i++) {
    uint32_t next = (i == size - 1) ? 0 : chain[i + 1];

    uint8_t buf[512] = {0};
    buf[0] = (next >> 0) & 0xFF;
    buf[1] = (next >> 8) & 0xFF;
    buf[2] = (next >> 16) & 0xFF;
    buf[3] = (next >> 24) & 0xFF;

    WriteSector(chain[i], buf, 512);
}

    return chain[0];
}






void ReadSector(uint32_t lba, uint8_t* buffer)
{



   for (int i = 0; i < 10000; i++) 
    {
        uint8_t status = inb(ATA_STATUS);
                 
        if (!(status & 0x80)) break;
    }

 
	
    outb(ATA_SECTOR_COUNT, 1);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, 0x20);
    	    

	 if (!ata_wait()) 
	  {
	           Print(55, 6, font_color_red, background_color, "ata read failed");

	      return;
	  }


    for (int i = 0; i <  512 / 2; i++) 
    {
        uint16_t data = inw(ATA_DATA);
        buffer[i * 2] = data & 0xFF;
        buffer[i * 2 + 1] = (data >> 8) & 0xFF;
    }





    
}

void WriteSector(uint32_t lba, const char *text, int sizeoftext)
{
 char buffer[512];

 for (int i = 0; i < 512; i++) 
 buffer[i] = 0;

 for (int j = 0; j < sizeoftext; j++) 
 {
 
  buffer[j] = text[j];
}
 
	
    outb(ATA_SECTOR_COUNT, 1);
    outb(ATA_LBA_LOW, lba & 0xFF);
    outb(ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(ATA_LBA_HIGH, (lba >> 16) & 0xFF);
    outb(ATA_COMMAND, 0x30);
    	    

    while ((inb(ATA_STATUS) & 0x08) == 0)
    {
     	
    }


    for (int i = 0; i < 512; i+=2) 
    {
	   uint16_t word = (uint8_t)buffer[i] | ((uint8_t)buffer[i+1] << 8);
       outw(ATA_DATA, word);
       
    }


    while(inb(ATA_STATUS) & 0x80)
    {
     	
    }
    
}

void CreateFile(const char* name, const char *ext, uint8_t size)
{

    
    for (int i = 0; i < ROOT_DIR_SECTORS; i++)
    {
        ReadSector(ROOT_DIR_LBA + i, buffer + (i * 512));
    }

    for (int i = 0; i < ROOT_DIR_SIZE; i += 16)
    {
        if (buffer[i] == 0)
        {
         
            for (int j = 0; j < 8 && name[j]; j++)
                buffer[i + j] = name[j];
            
		
            for (int j = 0; j < 3 && ext[j]; j++)
                buffer[i + 8 + j] = ext[j];

            uint32_t first_sector = AllocateFileSectors(size);

            PrintHex(first_sector, 0, 0);
         
            buffer[i + 11] = (first_sector >> 0) & 0xFF;
            buffer[i + 12] = (first_sector >> 8) & 0xFF;
            buffer[i + 13] = (first_sector >> 16) & 0xFF;
            buffer[i + 14] = (first_sector >> 24) & 0xFF;

            buffer[i + 15] = size;
            
    uint8_t sector[512];

    ReadSector(72, sector);
    Print(0, 3, font_color, background_color, "72 -");
    PrintHex(sector[0], 3, 5);
    PrintHex(sector[1], 3, 10);
    
    ReadSector(73, sector);
    Print(0, 4, font_color, background_color, "73 -");
    PrintHex(sector[0], 4, 5);
    PrintHex(sector[1], 4, 10);

    ReadSector(74	, sector);
    Print(0, 5, font_color, background_color, "74 -");
    PrintHex(sector[0], 5, 5);
    PrintHex(sector[1], 5, 10);

    ReadSector(75	, sector);
    Print(0, 6, font_color, background_color, "75 -");
    PrintHex(sector[0], 6, 5);
    PrintHex(sector[1], 6, 10);

    ReadSector(76, sector);
    Print(0, 7, font_color, background_color, "76 -");
    PrintHex(sector[0], 7, 5);
    PrintHex(sector[1], 7, 10);

    ReadSector(77	, sector);
    Print(0, 8, font_color, background_color, "77 -");
    PrintHex(sector[0], 8, 5);
    PrintHex(sector[1], 8, 10);

    ReadSector(78	, sector);
    Print(0, 9, font_color, background_color, "78 -");
    PrintHex(sector[0], 9, 5);
    PrintHex(sector[1], 9, 10);

    ReadSector(79	, sector);
    Print(0, 10, font_color, background_color, "79 -");
    PrintHex(sector[0], 10, 5);
    PrintHex(sector[1], 10, 10);

    ReadSector(80	, sector);
    Print(0, 11, font_color, background_color, "80 -");
    PrintHex(sector[0], 11, 5);
    PrintHex(sector[1], 11, 10);

    ReadSector(81	, sector);
    Print(0, 12, font_color, background_color, "81 -");
    PrintHex(sector[0], 12, 5);
    PrintHex(sector[1], 12, 10);


            


            for (int s = 0; s < ROOT_DIR_SECTORS; s++)
            {
            WriteSector(ROOT_DIR_LBA + s, buffer + (s * 512), 512);
            }
            return;
        }
    }

    Print(0, 20, font_color_red, background_color, "dir full");
}


void ShowFiles()
{



int y = 0;
int x = 0;

    uint8_t buffer[ROOT_DIR_SIZE];
    
    for (int i = 0; i < ROOT_DIR_SECTORS; i++)
    {
  	  ReadSector(ROOT_DIR_LBA + i, buffer + (i * 512));
    }
      

    
    for (int i = 0; i < ROOT_DIR_SIZE; i += 16)
    {
        if (buffer[i] != 0)
        {
            char name[9];
            char ext[4];
            
            for (int j = 0; j < 8; j++)
            {
            name[j] = buffer[i + j];
            if(name[j] != 0){x++;}
			}
			name[8] = '\0';
			
            for (int s = 0; s < 3; s++)
            ext[s] = buffer[i + 8 + s];
            ext[3] = '\0';

 			uint32_t sector =
            ((uint32_t)buffer[i + 11]) |
            ((uint32_t)buffer[i + 12] << 8) |
            ((uint32_t)buffer[i + 13] << 16) |
            ((uint32_t)buffer[i + 14] << 24);
           
	

            Print(0, 5 + y, font_color, background_color, name);
            Print(x, 5 + y, font_color, background_color, ".");
            Print(x+1, 5 + y, font_color, background_color, ext);
            PrintHex(sector, 5 + y, x + 5);

			x=0;
            y++;
            
           
            
        }
    }
}

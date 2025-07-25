#include <stdint.h>
#include "consts.h"

char InputBuffer[INPUTBUFFER_SIZE];
int InputLength = 0;

int CursorX = 9;
int CursorY = 1;

uint16_t table_background_color;
uint16_t background_color;
uint16_t font_color;
uint16_t font_color_red;
uint16_t font_color_blue;
uint16_t font_color_green;

char user[50] = "/user $ ";
uint16_t user_color;


int str_to_int(const char* str) 
{
    int result = 0;
    int i = 0;


    while (str[i] == ' ') 
    {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') 
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}
void int_to_str(unsigned int value, char* buffer) 
{
    int i = 0;

   
    do {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    } while (value != 0);

    buffer[i] = '\0';

   
    for (int j = 0; j < i / 2; j++) 
    {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}


int strcmp(const char *s1, const char *s2) 
{
    while (*s1 && (*s1 == *s2)) 
    {
        s1++;
        s2++;
    }



    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}



#include <stdint.h>
#include "consts.h"

char InputBuffer[INPUTBUFFER_SIZE];
int InputLength = 0;

int CursorX = 9;
int CursorY = 1;

uint16_t table_background_color;
uint16_t background_color;
uint16_t font_color;

char user[50] = "/user $ ";
uint16_t user_color;

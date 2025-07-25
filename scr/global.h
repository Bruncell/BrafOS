#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>

extern char InputBuffer[];
extern int InputLength;

extern int CursorX;
extern int CursorY;

extern uint16_t table_background_color;
extern uint16_t background_color;
extern uint16_t font_color;
extern uint16_t font_color_red;
extern uint16_t font_color_blue;
extern uint16_t font_color_green;

extern char user[50];
extern uint16_t user_color;

void int_to_str(unsigned int value, char* buffer);
int str_to_int(const char* str);
int strcmp(const char *s1, const char *s2);


#endif

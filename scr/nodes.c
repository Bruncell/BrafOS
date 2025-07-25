#include "global.h"
#include "consts.h"
#include "graphic.h"
#include "keyboard.h"
#include "consol.h"
#include "nodes.h"
#include "programs/bfs.h"
#include "programs/bfm.h"




static Token tokens[MAX_TOKENS];
static char *buffer;


void CutTokens()
{
for (int i = 0; i < MAX_TOKENS; i++) {
    tokens[i].Type = 0;

    for (int j = 0; j < INPUTBUFFER_SIZE; j++)
    tokens[i].Value[j] = '\0';
}


int token_count = 0;
int i = 0;



   while (InputBuffer[i] != '\0' && token_count < MAX_TOKENS)
   {
        static char word[INPUTBUFFER_SIZE];
        int j = 0;


   while (InputBuffer[i] == ' ')
   {
   i++;
   }


   while (InputBuffer[i] != ' ' && InputBuffer[i] != '\0' && j < INPUTBUFFER_SIZE - 1)
   {
       word[j++] = InputBuffer[i++];
   }
   word[j] = '\0';

   if (j > 0)
   {
            

if(strcmp(word, "echo") == 0)
    tokens[token_count].Type = TOK_ECHO;

if(strcmp(word, "help") == 0)
    tokens[token_count].Type = TOK_HELP;

if(strcmp(word, "reboot") == 0)
    tokens[token_count].Type = TOK_REBOOT;

if(strcmp(word, "clear") == 0)
    tokens[token_count].Type = TOK_CLEAR;

if(strcmp(word, "readsector") == 0)
    tokens[token_count].Type = TOK_READSECTOR;

if(strcmp(word, "showfiles") == 0)
    tokens[token_count].Type = TOK_SHOWFILES;

if(strcmp(word, "cfile") == 0)
    tokens[token_count].Type = TOK_CFILE;

if(strcmp(word, "bte") == 0)
    tokens[token_count].Type = TOK_BTE;

if(word[0] == '"' && word[j-1] == '"')
    tokens[token_count].Type = TOK_STR;

int p = 0;
for (int i = 0; word[i] != '\0'; i++) 
{
  if (word[i] < '0' || word[i] > '9') 
  {
            p = 1;
            break;
  }
}
if (p == 0) 
{
   tokens[token_count].Type = TOK_NUM;
}



int k = 0;
   for (int l = 0; l < j; l++)
   {
   if(word[l] != '"')
   {
   tokens[token_count].Value[k] = word[l];  
   }
   else
   {
   continue;
   }

    k++;      
   }
   tokens[token_count].Value[j] = '\0';
            
    token_count++;
    }
    }


   


for(; 0 < InputLength; InputLength--)
{
CursorX--;
DrawLetter(CursorX, CursorY, font_color, background_color, 0);
InputBuffer[InputLength] = '\0';
}

Nodes(token_count);	
}



void Nodes(int token_count)
{




if(tokens[0].Type == TOK_HELP && token_count == 1)
{ClearScreen();
    Print(0, 5, font_color, background_color, "\r- - - -help panel - - - -\r \r \rhelp - show commands \r \rclear - clear screen\r \r \r- - - - - - - - - - - - -");

}



if(tokens[0].Type == TOK_ECHO && tokens[1].Type == TOK_STR && token_count == 2)
{ClearScreen();

 Print(0, 5, font_color, background_color, tokens[1].Value);
    
}


if(tokens[0].Type == TOK_READSECTOR && tokens[1].Type == TOK_NUM && token_count == 2)
{ClearScreen();



ReadSector(str_to_int(tokens[1].Value) , buffer);

int y = 15;
int x = 0;
for(int i = 0; i < 512; i++)
{
DrawLetter(x, y, font_color, background_color, buffer[i]);


x++;
if(x == 80)
{
y++;
x=0;
}
}

}

if (tokens[0].Type == TOK_SHOWFILES  && token_count == 1)
{

ClearScreen();


ShowFiles();


}

if (tokens[0].Type == TOK_BTE && tokens[1].Type == TOK_STR  && token_count == 2)
{

ClearScreen();


BrafTextEditor(tokens[1].Value);


}

if (tokens[0].Type == TOK_CFILE && tokens[1].Type == TOK_STR && tokens[2].Type == TOK_NUM  && token_count == 3)
{

ClearScreen();
CreateFile( tokens[1].Value, "txt", str_to_int(tokens[2].Value));

}


if (tokens[0].Type == TOK_CLEAR  && token_count == 1)
{

ClearScreen();



}
	WriteConsol();	
}

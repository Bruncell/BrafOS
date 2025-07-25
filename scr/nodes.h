#include <stdint.h>

#ifndef NODES_H
#define NODES_H


#define MAX_TOKENS 10





typedef enum 
{
    TOK_REBOOT,  //0
    TOK_HELP,   //1
    TOK_ECHO,   //2
    TOK_CLEAR,   //3
    TOK_READSECTOR,   //4
    TOK_STR,   //5
    TOK_NUM,   //6
    TOK_SHOWFILES,   //6
    TOK_CFILE,   //6
    TOK_BTE,   //6


} TokenType;

typedef struct 
{
    TokenType Type;
    char Value[INPUTBUFFER_SIZE];

} Token;


void Nodes(int token_count);

#endif

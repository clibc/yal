#ifndef LEXER_H
#define LEXER_H
#include "tokens.h"
#include <stdlib.h>

void lex_line(char*, size_t);
int  lex_integer(char*, Token*);
void dump_tokens();

// Lexer definitions
#define KEYWORD_INT       "int"
#define KEYWORD_FLOAT     "float"
#define OPERATOR_PLUS     '+'
#define OPERATOR_MINUS    '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DEVIDE   '/'
#define OPERATOR_EQUAL    '='

#endif // LEXER_H

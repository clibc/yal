#ifndef LEXER_H
#define LEXER_H

#include "tokens.h"
#include <stdlib.h>

void lex_line(char*, size_t);
int  lex_integer(char*, Token*);
int  lex_entity(char* str, Token* s_token);
void dump_tokens();
int  get_next_token(Token **t);
int  show_next_token(Token **token);

// Lexer definitions
#define KEYWORD_INT        "int"
#define KEYWORD_FLOAT      "float"
#define OPERATOR_PLUS      '+'
#define OPERATOR_MINUS     '-'
#define OPERATOR_MULTIPLY  '*'
#define OPERATOR_DIVIDE    '/'
#define OPERATOR_EQUAL     '='

#define LEFT_PAR           '('
#define RIGHT_PAR          ')'

#define WHITESPACE_TAB     '\t'
#define WHITESPACE_SPACE   ' '
#define WHITESPACE_NEWLINE '\n'

#endif // LEXER_H

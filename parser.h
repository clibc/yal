#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include "tokens.h"

void parse_line(char* str, size_t size);
int  parse_integer(char* str, Token* int_token);

// Parser definitions
#define IDENTIFIER_INT     "int"
#define IDENTIFIER_FLOAT   "float"
#define IDENTIFIER_PLUS    '+'
#define IDENTIFIER_MINUS   '-'

#endif //

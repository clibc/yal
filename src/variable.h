#ifndef VARIABLE_H
#define VARIABLE_H

#include "tokens.h"

#define MAXNAME_SIZE 10

typedef struct{
	TokenSubType type;
	char name[MAXNAME_SIZE];

	union{
		int   int_value;
		float float_value;
		char  string[10];
	} data;
}Variable;

void       create_variable(Token *identifier, Token* exp);
Variable*  get_variable(char* name);

#endif // VARIABLE_H

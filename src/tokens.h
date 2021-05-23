#ifndef TOKENS_H
#define TOKENS_H

typedef enum{
	IDENTIFIER,
	KEYWORD,
	OPERATOR,
	LITERAL,
	SEPERATOR,
	COMMENT,
} TokenType;

typedef struct{
	TokenType type;
	
	union{
		int   int_value;
		float float_value;
		char  char_value;
		char  entity[20]; 
	}data;
} Token;

#endif // TOKENS_H

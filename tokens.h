#ifndef TOKENS_H
#define TOKENS_H

typedef enum{
	NUMBER,
	IDENTIFIER,
	LEFT_PAR,
	RIGHT_PAR,
	PLUS_OP,
	MINUS_OP,
	DIVIDE_OP,
} TokenType;


typedef struct{
	TokenType type;
	
	union{
		int int_value;
		float float_value;
		char char_value;
	}data;
} Token;

#endif

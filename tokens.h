#ifndef TOKENS_H
#define TOKENS_H

typedef enum{
	NUMBER,
	IDENTIFIER,
	OPERATOR
} TokenType;

typedef struct{
	TokenType type;
	
	union{
		int int_value;
		float float_value;
		char char_value;
	}data;
} Token;

#endif // TOKENS_H

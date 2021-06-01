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

typedef enum{
	INTEGER,
	FLOAT,
	STRING
} Literal_SB;

typedef struct{
	Literal_SB type;

	union{
		int   int_value;
		float float_value;
		char  string[15];
	}data;

} Literal_Token;

typedef struct{
	char op;
	int  precedence;
} Operator_SB;

typedef struct{
	TokenType type;
	
	union{
		int   int_value;
		float float_value;
		char  char_value;
		char  entity[20]; 
	}data;

	union{
		Literal_SB  literal;
		Operator_SB operator;
	}sub;
	
	// precedence for operators
	int op_pre;
} Token;

#endif // TOKENS_H

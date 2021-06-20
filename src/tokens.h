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
	STRING,
	FUNCDEF
} Literal_SB;

typedef enum{
	T_FLOAT,
	T_INTEGER,
} Keyword_SB;

typedef struct{
	Literal_SB type;

	union{
		int   int_value;
		float float_value;
		char  string[15];
	}data;
} Literal_Token;

typedef struct{
	char symbol;
	int  precedence;
} Operator_Token;

typedef struct{
	char string[15];
	union {
		Literal_SB type;
	}sub;
} Keyword_Token;

typedef struct{
	char string[15];
} Identifier_Token;

typedef struct{
	TokenType type;

	union{
		Literal_Token    literal;
		Operator_Token   operator;
		Keyword_Token    keyword;
		Identifier_Token identifier;
	}sub;
} Token;

#endif // TOKENS_H

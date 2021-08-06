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

/* typedef enum{ */
/* 	INTEGER, */
/* 	FLOAT, */
/* 	STRING, */
/* } Literal_SB; */

/* typedef enum{ */
/* 	T_INTEGER, */
/* 	T_FLOAT, */
/* 	T_STRING, */
/* 	T_FUNCDEF */
/* } Keyword_SB; */

typedef enum {
	LIT_INTEGER,
	LIT_FLOAT,
	LIT_STRING,

	KEY_INTEGER,
	KEY_FLOAT,
	KEY_STRING,
	KEY_FUNCDEF
} TokenSubType;

typedef struct{
	//Literal_SB type;
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
	//union {
	//	Keyword_SB type;
	//}sub;
} Keyword_Token;

typedef struct{
	char string[15];
} Identifier_Token;

typedef struct{
	TokenType type;
	TokenSubType subType;

	union{
		Literal_Token    literal;
		Operator_Token   operator;
		Keyword_Token    keyword;
		Identifier_Token identifier;
	}sub;
} Token;

#endif // TOKENS_H

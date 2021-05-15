enum ParserSymbols{
	DIGIT,
	IDENTIFIER,
	LEFT_PAR,
	RIGHT_PAR,
	PLUS_OP,
	MINUS_OP,
	DIVIDE_OP,
};

typedef struct{
	char* name;
	void* data;
}Variable;


struct Token{
	
	union{
		int int_value;
		float float_value;
		char char_value;
	}data;
};

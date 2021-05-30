#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "parser.h"

#ifdef _WIN32
#define GET_LINE												\
	char line[100];												\
	size_t line_size = sizeof(line);							\
	fgets(line, line_size, stdin)									
#elif __unix__
#define GET_LINE												\
	char *line = NULL;											\
	size_t line_size;											\
	getline(&line, &line_size, stdin)							
#endif


int main(void) {
	GET_LINE;
	lex_line(line, line_size);
	dump_tokens();
	parse_tokens();
	reset_lexer();
	
	while(1){
		// for testing variable
		getline(&line, &line_size, stdin);
		lex_line(line, line_size);
		parse_tokens();
		reset_lexer();
	}


	return EXIT_SUCCESS;
}

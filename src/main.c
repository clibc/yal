#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"
#include "parser.h"

#ifdef _WIN32
#define GET_LINE												\
	char line[100];												\
	size_t line_size = sizeof(line);							\
	fgets(line, 100, stdin)									
#elif __unix__
#define GET_LINE												\
	char *line = NULL;											\
	size_t line_size;											\
	getline(&line, &line_size, stdin)							
#endif


int main(void) {
	/// 86 + 78 - 36

	GET_LINE;
	
	lex_line(line, line_size);

	dump_tokens();

	parse_tokens();
	return EXIT_SUCCESS;
}

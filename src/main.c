#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"

int main(void) {
	/// 86 + 78 - 36
	char* str = NULL;
	size_t line_size;
	getline(&str, &line_size, stdin);

	lex_line(str, line_size);

	dump_tokens();
	return EXIT_SUCCESS;
}

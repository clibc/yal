#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"

int main(void) {
	/// 86 + 78 - 36
	char* str = NULL;
	size_t line_size;
	getline(&str, &line_size, stdin);
	fprintf(stdout, str);

	parse_line(str, line_size);

	return EXIT_SUCCESS;
}

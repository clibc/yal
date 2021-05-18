#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "parser.h"

int main(void) {
	/// 86 + 78 - 36
	/* char* str = NULL; */
	/* size_t line_size; */
	/* getline(&str, &line_size, stdin); */
	/* fprintf(stdout, str); */

	char line[100];
	fgets(line, 100, stdin);

	parse_line(line, sizeof(line));

	dump_tokens();
	return EXIT_SUCCESS;
}

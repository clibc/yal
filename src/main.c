#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

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


int main(int argc, char** argv) {
	if(argc == 1){
		while(1){
			// for testing variable
			GET_LINE;
			lex_line(line, line_size);
			dump_tokens();
			parse_tokens();
			reset_lexer();
		}
	}
	else {
		FILE *f = fopen(argv[1], "r");
		if(f == NULL){
			char* error_message = strerror(errno);
			printf("%s '%s'\n", error_message, argv[1]);
		}
		else{
			char *fbuffer;
			size_t fsize = 0;
			fseek(f, 0, SEEK_END);
			fsize = ftell(f);
			fseek(f, 0, SEEK_SET);

			fbuffer = (char*)malloc(fsize * sizeof(char));
			fread(fbuffer, sizeof(char), fsize, f);

			strtok(fbuffer, "\n");
			strtok(NULL, "\n");
			strtok(NULL, "\n");
			printf("%s\n", strtok(NULL, "\n"));
		}
			
	}

	return EXIT_SUCCESS;
}

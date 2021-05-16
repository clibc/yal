#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokens.h"

enum Parser_Types{
	LITERAL,
	OPERATOR
};

int main(void) {
	/// 86 + 78 - 36 
	char* str = NULL;
	size_t line_size;
	getline(&str, &line_size, stdin);
	fprintf(stdout, str);

	char storage[5];

	int i = 0;
	int c = 0;

	Token *tokens = malloc(sizeof(Token) * 5);

	tokens[0].type = NUMBER;
	tokens[0].data.int_value = 1;
	tokens[0].data.float_value = 1.0f;
	tokens[0].data.char_value = 'A';

	
	while(str[i] != '\n'){
		if(isdigit(str[i])){
			storage[c] = str[i];
			c += 1;
			printf("number detected\n");
		}
		else
		{
			if(c > 0){
				// This state means we have a number to be translated from text
				// get value from storage
				c = 0;
				int res = atoi(&storage[0]);
				printf("Got an integer :%d\n", res);
			}
			
			switch(str[i]){
			case '+':
				printf("Plus detected\n");
				break;
			case '-':
				printf("Minus detected\n");
				break;
			case ' ':
				break;

			default:
				printf("Undefined Identifier\n");
				exit(EXIT_FAILURE);
			}
		}
		
		
		i += 1;
	}

	return EXIT_SUCCESS;
}

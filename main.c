#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "tokens.h"

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
	int tokenCounter = 0;
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
				tokens[tokenCounter].type = NUMBER;
				tokens[tokenCounter].data.int_value = res;
				tokenCounter++;
			}
			
			switch(str[i]){
			case '+':
				printf("Plus detected\n");
				tokens[tokenCounter].type = OPERATOR;
				tokens[tokenCounter].data.char_value = '+';
				tokenCounter++;
				break;
			case '-':
				printf("Minus detected\n");
				tokens[tokenCounter].type = OPERATOR;
				tokens[tokenCounter].data.char_value = '-';
				tokenCounter++;
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

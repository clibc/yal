#include "parser.h"
#include <ctype.h>
#include <stdio.h>

void parse_line(char* str, size_t size){
	Token tokens[30]; // We store tokens here

	int integer_count = 0; // count of parsed intigers
	int tokenCounter = 0; // count of tokens

	char int_storage[10]; // Integer
	char identifier_storage[100]; // For storing yet defined identifiers

	for(int i = 0; i < (int)size; ++i){
		if(isdigit(str[i])){
			int_storage[integer_count] = str[i];
			integer_count += 1;

			int shifted = parse_integer(&str[i], &tokens[tokenCounter++]);
			i += shifted;
			//printf("number detected\n");
		}
		else
			{
				switch(str[i]){
				case IDENTIFIER_PLUS:
					printf("Plus detected\n");
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = '+';
					tokenCounter++;
					break;
				case IDENTIFIER_MINUS:
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
	}
	
}

int parse_integer(char* str, Token* int_token){
	char *base_ptr = str;
	int_token->type = NUMBER;

	char storage[10];
	int shifted_char = 0;

	while(1){
		if(isdigit(*base_ptr)){
			storage[shifted_char] = *base_ptr;
			base_ptr++;
			shifted_char += 1;
		}
		else break;
	}

	int_token->data.int_value = atoi(&storage[0]);
	return shifted_char-1;
}

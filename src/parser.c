#include "parser.h"
#include <ctype.h>
#include <stdio.h>

static Token tokens[30];
static int tokenCounter = 0; // count of tokens

void parse_line(char* str, size_t size){
	int integer_count = 0; // count of parsed intigers
	
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
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = '+';
					tokenCounter++;
					break;
				case IDENTIFIER_MINUS:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = '-';
					tokenCounter++;
					break;
				case ' ':
				case '\n':
					break;
				default:
					printf("Undefined Identifier %c\nASCII index : %d\n", str[i], (int)str[i]);
					break;
				}
			}
		if(str[i] == '\0')
			break;

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

void dump_tokens(){
	for(int i = 0; i < tokenCounter; ++i){
		Token *token = &tokens[i];
		printf("Token type : ");
		switch(token->type){
		case NUMBER:
			printf("NUMBER\n");
			printf("Value : %d\n", token->data.int_value);
			break;
		case OPERATOR:
			printf("OPERATOR\n");
			printf("Value : %c\n", token->data.char_value);
			break;
		default:
			break;
		}
		printf("------------\n");
	}
}

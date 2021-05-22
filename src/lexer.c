#include "lexer.h"
#include <ctype.h>
#include <stdio.h>

static Token tokens[100];
static int tokenCounter = 0; // count of tokens

void lex_line(char* str, size_t size){
	int integer_count = 0; // count of parsed intigers
	char identifier_storage[100]; // For storing yet defined identifiers
	
	for(int i = 0; i < (int)size; ++i){
		// TODO : Check if char in range of [48-57] | [65-90] | [97-122]
		// Which is potential literal according to ASCII table.
		// if char is not in that range it is probably operator or other token type.
		if(isdigit(str[i])){
			int shifted = lex_integer(&str[i], &tokens[tokenCounter++]);
			i += shifted;
		}
		else
			{
				switch(str[i]){
				case OPERATOR_PLUS:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = OPERATOR_PLUS;
					tokenCounter += 1;
					break;
				case OPERATOR_MINUS:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = OPERATOR_MINUS;	
					tokenCounter += 1;
				break;
				case OPERATOR_MULTIPLY:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = OPERATOR_MULTIPLY;
					tokenCounter += 1;
					break;
				case OPERATOR_DEVIDE:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = OPERATOR_DEVIDE;
					tokenCounter += 1;
					break;
				case OPERATOR_EQUAL:
					tokens[tokenCounter].type = OPERATOR;
					tokens[tokenCounter].data.char_value = OPERATOR_EQUAL;
					tokenCounter += 1;
					break;

				case ' ':
				case '\n':
				case '\t':
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

int lex_integer(char* str, Token* int_token){
	char *base_ptr = str;
	int_token->type = LITERAL;

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
		case LITERAL:
			printf("LITERAL\n");
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

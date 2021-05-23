#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static Token tokens[100];
static int tokenCounter = 0; // count of tokens

static int check_whitespace(char c){
	switch(c){
	case WHITESPACE_TAB:
	case WHITESPACE_SPACE:
	case WHITESPACE_NEWLINE:
		return 1;
	default:
		return 0;
	}
}

static int check_keyword(char* word){
	if(strcmp(word, KEYWORD_INT) == 0){
		return 1;
	}
	else if(strcmp(word, KEYWORD_FLOAT) == 0){
		return 1;
	}
	return 0;
}

void lex_line(char* str, size_t size){
	for(int i = 0; i < (int)size; ++i){
		if(isdigit(str[i])){
			int shifted = lex_integer(&str[i], &tokens[tokenCounter++]);
			i += shifted;
		}
		else if(isalpha(str[i])){
			int shifted = lex_entity(&str[i], &tokens[tokenCounter++]);
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

	storage[shifted_char] = '\0';
	int_token->data.int_value = atoi(&storage[0]);
	return shifted_char-1;
}

int lex_entity(char* str, Token* s_token){
	char *base_ptr = str;

	char storage[20];
	int shifted_char = 0;

	while(1){
		if(isalpha(*base_ptr) || isdigit(*base_ptr)){
			storage[shifted_char] = *base_ptr;
			base_ptr += 1;
			shifted_char += 1;
		}
		else
			break; //End of the entity
	}

	storage[shifted_char] = '\0';
	if(check_keyword(storage)){
		s_token->type = KEYWORD;
	}
	else{
		s_token->type = IDENTIFIER;
	}

	strcpy(s_token->data.entity, storage);
	return shifted_char - 1;
}

void dump_tokens(){
	for(int i = 0; i < tokenCounter; ++i){
		Token *token = &tokens[i];
		printf("Token type : ");
		switch(token->type){
		case LITERAL:
			printf("LITERAL\n");
			printf("Int value : %d\n", token->data.int_value);
			break;
		case OPERATOR:
			printf("OPERATOR\n");
			printf("Value : %c\n", token->data.char_value);
			break;
		case IDENTIFIER:
			printf("IDENTIFIER\n");
			printf("Value : %s\n", token->data.entity);
			break;
		case KEYWORD:
			printf("KEYWORD\n");
			printf("Value : %s\n", token->data.entity);
			break;
		default:
			break;
		}
		printf("------------\n");
	}
}

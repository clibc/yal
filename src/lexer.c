#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static Token tokens[100];
static int tokenCounter = 0; // count of tokens
static int t_count = 0;

void reset_lexer(){
	tokenCounter = 0;
	t_count = 0;
}

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

static TokenSubType check_keyword(char* word){
	if(strcmp(word, KEYWORD_INT) == 0){
		return KEY_INTEGER; 
	}
	else if(strcmp(word, KEYWORD_FLOAT) == 0){
	    return KEY_FLOAT;
	}
	else if(strcmp(word, KEYWORD_STRING) == 0){
	    return KEY_STRING;
	}
	else if(strcmp(word, KEYWORD_FUNCDEF) == 0){
	    return KEY_FUNCDEF;
	}
	return -1;
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
					tokens[tokenCounter].type                    = OPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = OPERATOR_PLUS;
					tokens[tokenCounter].sub.operator.precedence = 1;
					tokenCounter += 1;
					break;
				case OPERATOR_MINUS:
					tokens[tokenCounter].type                    = OPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = OPERATOR_MINUS;
					tokens[tokenCounter].sub.operator.precedence = 1;
					tokenCounter += 1;
					break;
				case OPERATOR_MULTIPLY:
					tokens[tokenCounter].type                    = OPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = OPERATOR_MULTIPLY;
					tokens[tokenCounter].sub.operator.precedence = 2;
					tokenCounter += 1;
					break;
				case OPERATOR_DIVIDE:
					tokens[tokenCounter].type                    = OPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = OPERATOR_DIVIDE;
					tokens[tokenCounter].sub.operator.precedence = 2;
					tokenCounter += 1;
					break;
				case OPERATOR_EQUAL:
					tokens[tokenCounter].type                     = OPERATOR;
					tokens[tokenCounter].sub.operator.symbol      = OPERATOR_EQUAL;
					tokenCounter += 1;
					break;
				case LEFT_PAR:
					tokens[tokenCounter].type                    = SEPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = LEFT_PAR;
					tokenCounter += 1;
					break;
			    case RIGHT_PAR:
					tokens[tokenCounter].type                    = SEPERATOR;
					tokens[tokenCounter].sub.operator.symbol     = RIGHT_PAR;
					tokenCounter += 1;
					break;
					
				case  WHITESPACE_TAB:
				case  WHITESPACE_SPACE:
				case  WHITESPACE_NEWLINE:
				case  0:
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

	char storage[10];
	int shifted_char = 0;

	for(;;){
		if(isdigit(*base_ptr)){
			storage[shifted_char] = *base_ptr;
			base_ptr     += 1;
			shifted_char += 1;
		}
		else if(*base_ptr == '.'){
			// parsing floating point
			storage[shifted_char]  = *base_ptr;
			shifted_char          += 1;
			base_ptr              += 1;

			for(;;){
				if(isdigit(*base_ptr)){
					storage[shifted_char]  = *base_ptr;
					base_ptr              += 1;
					shifted_char          += 1;
				}
				else{ // end parsing float construct token and return
					int_token->type                         = LITERAL;
					int_token->subType                      = LIT_FLOAT;
					int_token->sub.literal.data.float_value = atof(&storage[0]);
					return shifted_char - 1;
				}
			}
		}
		else break;
	}

	storage[shifted_char] = '\0';
	
	int_token->type                       = LITERAL;
	int_token->subType                    = LIT_INTEGER;
	int_token->sub.literal.data.int_value = atoi(&storage[0]);
	return shifted_char - 1;
}

int lex_entity(char* str, Token* s_token){
	char *base_ptr = str;

	char storage[20];
	int shifted_char = 0;

	for(;;){
		if(isalpha(*base_ptr) || isdigit(*base_ptr)){
			storage[shifted_char] = *base_ptr;
			base_ptr += 1;
			shifted_char += 1;
		}
		else
			break; //End of the entity
	}

	storage[shifted_char] = '\0';
	
	TokenSubType keywordType = check_keyword(storage);
	if((int)keywordType != -1){
		s_token->type = KEYWORD;
		strcpy(s_token->sub.keyword.string, storage);

		s_token->subType = keywordType;
	}
	else{
		s_token->type = IDENTIFIER;
		strcpy(s_token->sub.identifier.string, storage);
	}

	return shifted_char - 1;
}

void dump_tokens(){
	for(int i = 0; i < tokenCounter; ++i){
		Token *token = &tokens[i];
		printf("Token type : ");
		switch(token->subType){
		case LITERAL:
			switch(token->subType){
			case LIT_INTEGER:
				printf("LITERAL INTEGER\n");
				printf("Value : %d\n", token->sub.literal.data.int_value);
				break;
			case LIT_FLOAT:
				printf("LITERAL FLOAT\n");
				printf("Value : %f\n", token->sub.literal.data.float_value);
				break;
			case LIT_STRING:
				printf("LITERAL STRING\n");
				printf("Value : %s\n", token->sub.literal.data.string);
				break;
			}
			break;
		case OPERATOR:
			printf("OPERATOR\n");
			printf("Value : %c\n", token->sub.operator.symbol);
			printf("Precedence : %d\n", token->sub.operator.precedence);
			break;
		case IDENTIFIER:
			printf("IDENTIFIER\n");
			printf("Value : %s\n", token->sub.identifier.string);
			break;
		case KEYWORD:
			printf("KEYWORD\n");
			printf("Value : %s\n", token->sub.keyword.string);
			break;
		case SEPERATOR:
			printf("SEPERATOR\n");
			printf("Symbol : %c\n", token->sub.operator.symbol);
		default:
			break;
		}
		printf("------------\n");
	}
}

int get_next_token(Token **token){
	if(t_count < tokenCounter){
		*token = &tokens[t_count];
		t_count += 1;
		return 1;
	}
	printf("ERROR: Ran out of tokens\n");
	return 0;
}

int show_next_token(Token **token){
	if(t_count < tokenCounter){
		*token = &tokens[t_count];
		return 1;
	}
	return 0;
}

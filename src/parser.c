#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

static void lookahead_literal_int(Token *t);

void parse_tokens(void){
	Token *t;

	if(get_next_token(&t)){ // this is the first token we get, so there are few possibilities

		switch (t->type){
		case IDENTIFIER:
			printf("Undefined Identifier : %s\n", t->data.entity );
			exit(EXIT_FAILURE);
		case OPERATOR:
			printf("Unexpected operator : %c\n", t->data.char_value);
			exit(EXIT_FAILURE);
		case LITERAL:
			lookahead_literal_int(t);
		default:
			break;
		}
		

	}
}

static void lookahead_literal_int(Token *t){
	// if this happens there is a token and we need to parse others
	Token *next_token;
	if(get_next_token(&next_token)){
		if(next_token->type == OPERATOR){
			Token *other_operand;
			if(get_next_token(&other_operand)){
				// we got other operand and it is time to do actual operation
				// and we dont care about operator precedence yet
				if(other_operand->type == LITERAL){
					int result = 0;
					switch(next_token->data.char_value){
					case OPERATOR_PLUS:
						result = t->data.int_value + other_operand->data.int_value;
						break;
					case OPERATOR_MINUS:
						result = t->data.int_value - other_operand->data.int_value;
						break;
					case OPERATOR_MULTIPLY:
						result = t->data.int_value * other_operand->data.int_value;
						break;
					case OPERATOR_DEVIDE:
						result = t->data.int_value / other_operand->data.int_value;
						break;
					default:
						break;
					}
					printf("Result : %d\n", result);
				}
				else{
					// second operator is not as expected
					printf("ERROR: Trying to operate two different thing.\n");
				}
			}
			else{
				//there is no token after operator
				printf("ERROR: No operand after operator %c\n", next_token->data.char_value);
			}
		}
	}
	else{
		printf("%d\n", t->data.int_value);
	}
}

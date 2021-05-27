#include "parser.h"
#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

static void lookahead_literal_int(Token *t);
static Token parse_expression();

void parse_tokens(void){
	Token *t;
	Token exp_result;
	if(show_next_token(&t)){ // this is the first token we get, so there are few possibilities
		switch (t->type){
		case IDENTIFIER:
			printf("Undefined Identifier : %s\n", t->data.entity );
			exit(EXIT_FAILURE);
		case OPERATOR:
			printf("Unexpected operator : %c\n", t->data.char_value);
			exit(EXIT_FAILURE);
		case LITERAL:
			 exp_result = parse_expression();
			 printf("result = %d\n", exp_result.data.int_value);
		default:
			break;
		}
	}
}

static void lookahead_literal_int(Token *t){
	// if this happens there is a token and we need to parse others
	Token *op_token;
	if(get_next_token(&op_token)){
		if(op_token->type == OPERATOR){
			Token *other_operand;
			if(get_next_token(&other_operand)){
				// we got other operand and it is time to do actual operation
				// and we dont care about operator precedence yet
				if(other_operand->type == LITERAL){
					int result = 0;
					switch(op_token->data.char_value){
					case OPERATOR_PLUS:
						result = t->data.int_value + other_operand->data.int_value;
						break;
					case OPERATOR_MINUS:
						result = t->data.int_value - other_operand->data.int_value;
						break;
					case OPERATOR_MULTIPLY:
						result = t->data.int_value * other_operand->data.int_value;
						break;
					case OPERATOR_DIVIDE:
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
				printf("ERROR: No operand after operator %c\n", op_token->data.char_value);
			}
		}
	}
	else{
		printf("%d\n", t->data.int_value);
	}
}

static Token parse_expression(){
	// assuming starting token is literal number

	int output_count = 0;
	int op_count = 0;
	
	Token output[20];
	Token op_stack[20];
	
	Token *n_token;
	while(1){
		if(get_next_token(&n_token)){
			if(n_token->type == OPERATOR){	
				while(op_count > 0 &&
					  op_stack[op_count-1].op_pre > n_token->op_pre &&
					  op_stack[op_count-1].op_pre == n_token->op_pre){

					output[output_count] = op_stack[op_count];
					op_count     -= 1;
					output_count += 1;
				}
				op_stack[op_count] = *n_token; 
				op_count += 1;
			}
			else if(n_token->type == LITERAL){
				// we need sub_token type for literals line numbers, string etc..
				// And need to check if this is number, for now we assume  literal input is always a number
				output[output_count] = *n_token;
				output_count += 1;
			}
			else{
				printf("Unexpected token. %s (Expected : 'OPERATOR' OR 'LITERAL')\n", n_token->data.entity);
				exit(EXIT_FAILURE);
			}
		}
		else break; // For now we only parse math expr, but we probably need to detect if ; token is come up?
	}

	while(op_count > 0){
		output[output_count] = op_stack[op_count - 1];
		op_count     -= 1;
		output_count += 1;
	}

	// calculate post-fix notation
	Token result;
	result.type = LITERAL;
	
	Token p_stack[20];
	int   p_counter = 0;
		
		
	int iterator = 0;
	while(output_count > 0){
		if(output[iterator].type == LITERAL){
			p_stack[p_counter] = output[iterator];
			p_counter += 1;
		}
		else if(output[iterator].type == OPERATOR){
			Token t2 = p_stack[p_counter-1]; // second operand
			Token t1 = p_stack[p_counter-2]; // first operand
			p_counter -= 2;

			switch(output[iterator].data.char_value){
			case OPERATOR_PLUS:
				result.data.int_value = t1.data.int_value + t2.data.int_value;
				break;
			case OPERATOR_MINUS:
				result.data.int_value = t1.data.int_value - t2.data.int_value;
				break;
			case OPERATOR_MULTIPLY:
				result.data.int_value = t1.data.int_value * t2.data.int_value;
				break;
			case OPERATOR_DIVIDE:
				result.data.int_value = t1.data.int_value / t2.data.int_value;
				break;
			}

			p_stack[p_counter] = result;
			p_counter += 1;
		}
		iterator += 1;
		output_count -= 1;
	}
	
	return result;
}

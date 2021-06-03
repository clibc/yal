#include "parser.h"
#include "lexer.h"
#include "variable.h"
#include <stdio.h>
#include <stdlib.h>

static Token parse_expression(void);
static void  parse_variable_decl(void);

void parse_tokens(void){
	Token *t;
	Token exp_result;
	Variable *var;
	if(show_next_token(&t)){ // this is the first token we get, so there are few possibilities
		switch (t->type){
		case IDENTIFIER:
			var = get_variable(t->sub.identifier.string);
			if(var != NULL){
				if(var->type == INTEGER)
					printf("%s = %d\n", var->name, var->data.int_value);
				else if(var->type == FLOAT)
					printf("%s = %f\n", var->name, var->data.float_value);
			}
			else{
				printf("ERROR: Undefined identifier %s\n", t->sub.literal.data.string);
				exit(EXIT_FAILURE);
			}
			break;
		case OPERATOR:
			printf("Unexpected operator : %c\n", t->sub.operator.symbol);
			exit(EXIT_FAILURE);
		case LITERAL:
		case SEPERATOR:
			exp_result = parse_expression();
			if(exp_result.type == LITERAL){
				if(exp_result.sub.literal.type == INTEGER)
					printf("result = %d\n", exp_result.sub.literal.data.int_value);
				else if(exp_result.sub.literal.type == FLOAT)
					printf("result = %f\n", exp_result.sub.literal.data.float_value);
			}
			break;
	    case KEYWORD: // Assuming it is a type keyword
			parse_variable_decl();
			break;
		default:
			break;
		}
	}
}

static Token parse_expression(void){
	// assuming starting token is literal number

	int output_count = 0;
	int op_count = 0;
	
	Token output[20];
	Token op_stack[20];
	
	Token *n_token;
	while(1){
		if(get_next_token(&n_token)){ // here running out of tokens
			if(n_token->type == OPERATOR){	
				while(op_count > 0 &&
					  (op_stack[op_count-1].sub.operator.precedence > n_token->sub.operator.precedence ||
					  op_stack[op_count-1].sub.operator.precedence == n_token->sub.operator.precedence) &&
					  op_stack[op_count-1].sub.operator.symbol != LEFT_PAR){
					// Possible bug on the last comparison (uninitilized memory address could have the same value as LEFT_PAR (40)

					output[output_count] = op_stack[op_count-1];
					op_count     -= 1;
					output_count += 1;
				}
				op_stack[op_count] = *n_token; 
				op_count += 1;
			}
			else if(n_token->type == LITERAL &&
					(n_token->sub.literal.type == INTEGER || n_token->sub.literal.type == FLOAT)){
				output[output_count] = *n_token;
				output_count += 1;
			}
			else if(n_token->type == SEPERATOR){
				if(n_token->sub.operator.symbol == LEFT_PAR){
					op_stack[op_count] = *n_token; 
					op_count += 1;			
				}
				else if(n_token->sub.operator.symbol == RIGHT_PAR){
					while(op_stack[op_count - 1].sub.operator.symbol != LEFT_PAR){
						output[output_count] = op_stack[op_count-1];
						op_count     -= 1;
						output_count += 1;
					}
					if(op_stack[op_count - 1].sub.operator.symbol == LEFT_PAR)
						op_count -= 1;					
				}
			}
			else{
				printf("ERROR: Unexpected token '%s' (Expected : 'OPERATOR' OR 'LITERAL')\n", n_token->sub.literal.data.string);
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

	// --------------- calculate post-fix notation  ---------------
	Token result;
	result.type = LITERAL;

	// What if there is only literal in output stack 
	// e.g int a = 5
	// then we need to return value of that token immediately.
	if(output_count == 1){ 
		if(output[output_count - 1].sub.literal.type == INTEGER){
			result.sub.literal.type           = INTEGER;
			result.sub.literal.data.int_value = output[output_count - 1].sub.literal.data.int_value;
		}
		else if(output[output_count - 1].sub.literal.type == FLOAT){
			result.sub.literal.type             = FLOAT;
			result.sub.literal.data.float_value = output[output_count - 1].sub.literal.data.float_value;
		}
		return result;
	}

	
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

			switch(output[iterator].sub.operator.symbol){
			case OPERATOR_PLUS:
				if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.int_value = t1.sub.literal.data.int_value + t2.sub.literal.data.int_value;
					result.sub.literal.type = INTEGER;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value + t2.sub.literal.data.int_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.int_value + t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value + t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
					
				break;
			case OPERATOR_MINUS:
				if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.int_value = t1.sub.literal.data.int_value - t2.sub.literal.data.int_value;
					result.sub.literal.type = INTEGER;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value - t2.sub.literal.data.int_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.int_value - t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value - t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				break;
			case OPERATOR_MULTIPLY:
				if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.int_value = t1.sub.literal.data.int_value * t2.sub.literal.data.int_value;
					result.sub.literal.type = INTEGER;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value * t2.sub.literal.data.int_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.int_value * t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value * t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				break;
			case OPERATOR_DIVIDE:
				if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.int_value = t1.sub.literal.data.int_value / t2.sub.literal.data.int_value;
					result.sub.literal.type = INTEGER;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == INTEGER){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value / t2.sub.literal.data.int_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == INTEGER && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.int_value / t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
				else if(t1.sub.literal.type == FLOAT && t2.sub.literal.type == FLOAT){
					result.sub.literal.data.float_value = t1.sub.literal.data.float_value / t2.sub.literal.data.float_value;
					result.sub.literal.type = FLOAT;
				}
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

static void parse_variable_decl(void){
	// <TYPE_KEYWORD> <IDENDTIFIER> <EQUAL_OPERATOR>
	// then call parse_expression and store return value in memory
	Token *n_token;

	if(get_next_token(&n_token)){
		// Check if token is keyword
		if(n_token->type == KEYWORD){
			// TODO : Make 'subtype' like TYPE_KEYWORD etc...
			// This section assumes type can only be int
			Token *identifier_token;
			get_next_token(&identifier_token);

			Token *equal_token;
			get_next_token(&equal_token);
			if(equal_token->type                 == OPERATOR &&
			   equal_token->sub.operator.symbol  == OPERATOR_EQUAL){
				Token result = parse_expression();

				if(result.sub.literal.type == n_token->sub.keyword.sub.type){
					create_variable(identifier_token, &result);
				}
				else{
					printf("ERROR : Variable type is not same with the result\n");
					exit(EXIT_FAILURE);
				}
				
			}
			else{
				printf("ERROR: Expected OPERATOR_EQUAL, but got %s\n", equal_token->sub.literal.data.string);
				exit(EXIT_FAILURE);
			}
		}
		else{
			printf("ERROR: Expected KEYWORD\n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		printf("Uncompleted assignment \n");
		exit(EXIT_FAILURE);
	}
	
}

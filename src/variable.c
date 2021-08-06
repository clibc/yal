#include "variable.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Variable vars[100];
int var_count = 0;

Variable* get_variable(char* name){
	for(int i = 0; i < var_count; ++i){
		if(strcmp(vars[i].name, name) == 0){
			Variable *var = &vars[i];
			return var;
		}
	}
	return NULL;
}

/* void create_variable(char* name, int value, int type){ */
/* 	Variable *var = get_variable(name); */
/* 	if(var != NULL){ */
/* 		printf("ERROR: variable '%s' does already exist\n", name); */
/* 		exit(EXIT_FAILURE); */
/* 	} */

/* 	if(type == INTEGER){ */
/* 		vars[var_count].data.int_value = value; */
		
/* 	} */
	
/* 	strcpy(vars[var_count].name, name);  */
/* 	var_count += 1; */
/* } */


void create_variable(Token *identifier, Token* exp){
	Variable *var = get_variable(identifier->sub.literal.data.string);
	if(var != NULL){
		printf("ERROR: variable '%s' does already exist\n", identifier->sub.identifier.string);
		exit(EXIT_FAILURE);
	}

	if(exp->subType == LIT_INTEGER){
		vars[var_count].type = LIT_INTEGER;
		vars[var_count].data.int_value = exp->sub.literal.data.int_value; 
	}
	else if(exp->subType == LIT_FLOAT){
		vars[var_count].type = LIT_FLOAT;
		vars[var_count].data.float_value = exp->sub.literal.data.float_value;
	}
	
	strcpy(vars[var_count].name, identifier->sub.identifier.string); 
	var_count += 1;
}

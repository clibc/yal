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

void create_variable(char* name, int value){
	Variable *var = get_variable(name);
	if(var != NULL){
		printf("ERROR: variable '%s' does already exist\n", name);
		exit(EXIT_FAILURE);
	}

	strcpy(vars[var_count].name, name); 
	vars[var_count].value = value;
	var_count += 1;
}

#include "variable.h"

#include <stdio.h>
#include <string.h>

Variable vars[100];
int var_count = 0;

void create_variable(char* name, int value){
	vars[var_count].name  = name;
	vars[var_count].value = value;
	var_count += 1;
}

Variable* get_variable(char* name){
	for(int i = 0; i < var_count; ++i){
		if(strcmp(vars[i].name, name) == 0){
			return &vars[i];
		}
	}
	return NULL;
}

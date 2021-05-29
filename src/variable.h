// we only support int type vars for now
typedef struct{
	char* name;
	int value;
}Variable;

void       create_variable(char* name, int value);
Variable*  get_variable(char* name);

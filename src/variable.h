// we only support int type vars for now

#define MAXNAME_SIZE 10

typedef struct{
	char name[MAXNAME_SIZE];
	int  value;
}Variable;

void       create_variable(char* name, int value);
Variable*  get_variable(char* name);

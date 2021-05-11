%%
"5" return 5;
"6" return 6;
. printf("unexpected character");
%%

int yywrap(void){
	return 1;
}

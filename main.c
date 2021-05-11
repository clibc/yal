#include <stdio.h>

extern int yylex();

int main(void)
{
	int nextToken = yylex();
	while(nextToken){
		switch(nextToken){
		case 5:
			printf("Token is 5");
			break;
		case 6:
			printf("Token is 6");
			break;
		default:
			break;
		}
		nextToken = yylex();
	}

	return 0;
}

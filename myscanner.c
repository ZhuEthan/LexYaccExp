/*************************************************************************
	> File Name: myscanner.c
	> Author: zhuyisong
	> Mail: zhuyisong1994@gmail.com
	> Created Time: Wed Jun  9 12:10:28 2021
 ************************************************************************/

#include <stdio.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char* names[] = {
	NULL, "db_type", "db_name", "db_table_prefix", "db_port"
};

int main(void) {
	int ntoken, vtoken;

	ntoken = yylex();
	while(ntoken) {
		printf("%d\n", ntoken);
		if(yylex() != COLON) {
			printf("Syntax error in line %d, Expected a ';' but found %s\n", yylineno, yytext);
			return 1;
		}
		vtoken = yylex();
		switch (ntoken) {
			case TYPE:
			case NAME:
			case TABLE_PREFIX:
				if (vtoken != IDENTIFIER) {
					printf("Syntax error in line %d, Expected a ';' but found %s\n", yylineno, yytext);
					return 1;
				}
				printf("%s is set to %s\n", names[ntoken], yytext);
				break;
			case PORT:
				if (vtoken != INTEGER) {
					printf("Syntax error in line %d, Expected a ';' but found %s\n", yylineno, yytext);
					return 1;
				}
				printf("%s is set to %s\n", names[ntoken], yytext);
				break;
			default: 
				printf("Syntax error in line %d\n", yylineno);
				break;
		}
		ntoken = yylex();
	}
	return 0;
}

%{
#include<stdio.h>
#include<stdlib.h>
void yyerror(char *s);
int yylex();
%}
%token ID
%%
S : ID '\n' { printf("Valid Variable\n"); };
%%
void yyerror(char *s)
{
printf("Invalid Variable\n");
}
int main()
{
yyparse();
}
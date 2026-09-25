%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(char *);

%}
%token FOR ID NUM
%%
stmt : FOR '(' ID '=' NUM ';'
ID '<' NUM ';'
ID '+' '+'
')'
{
printf("Valid FOR Statement\n");
};
%%
void yyerror(char *s)
{
printf("Invalid FOR Statement\n");
}
int main()
{
yyparse();
}
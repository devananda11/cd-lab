
%{
#include <stdio.h>

int yylex();
int yyerror(char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
input:
    expression '\n' { printf("Result = %d\n", $1); }
    ;

expression:
      expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { $$ = $1 / $3; }
    | '(' expression ')'       { $$ = $2; }
    | NUMBER                   { $$ = $1; }
    ;
%%

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Invalid expression\n");
    return 0;
}

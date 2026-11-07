%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token LETTER DIGIT NL

%%
start : var NL
        {
            printf("Valid variable\n");
            exit(0);
        }
      ;

var : LETTER rest
    ;

rest : LETTER rest
     | DIGIT rest
     |
     ;
%%

void yyerror(const char *s)
{
    printf("Invalid variable\n");
}

int main()
{
    printf("Enter a variable: ");
    yyparse();
    return 0;
}

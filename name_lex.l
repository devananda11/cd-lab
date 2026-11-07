
%{
#include <stdio.h>
%}

%%
.*[Dd][Ee][Vv][Aa].*    { printf("Rejected\n"); }
.*                      { printf("Accepted\n"); }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string:\n");
    yylex();
    return 0;
}

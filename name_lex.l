%{
#include<stdio.h>
%}
%%
.*ABCD.* { printf("Rejected\n"); }
.* { printf("Accepted\n"); }
%%
int yywrap()
{
return 1;
}
int main()
{
printf("Enter String:\n");
yylex();
return 0;
}
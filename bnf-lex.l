%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval.num = atoi(yytext); return NUM; }
[+]         { return '+'; }
[-]         { return '-'; }
[*]         { return '*'; }
[/]         { return '/'; }
[(]         { return '('; }
[)]         { return ')'; }
[ \t]       ;
\n          return '\n';
.           return yytext[0];

%%

int yywrap()
{
    return 1;
}
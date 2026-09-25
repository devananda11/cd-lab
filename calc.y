%{
    #include<stdio.h>
    #include<stdlib.h>
    int yylex();
    void yyerror(char *s);

%}
%token NUM
%%
line:exp'\n'{printf("Result=%d\n",$1);};
exp:exp'+'exp{$$=$1+$3;}
| exp'-'exp{$$=$1-$3;}
| exp'*'exp{$$=$1*$3;}
| exp'/'exp{$$=$1/$3;}
| NUM {$$=$1;}
;
%%
void yyerror(char *s){}
int main(){
    yyparse();
}
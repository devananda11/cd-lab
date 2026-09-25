%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char data[20];
    struct node *left;
    struct node *right;
};

struct node* createNode(char data[], struct node *left, struct node *right);
void preorder(struct node *root);
void yyerror(char *s);
int yylex();

struct node *root;
%}

%union
{
    int num;
    struct node *ptr;
}

%token <num> NUM
%type <ptr> E T F

%left '+' '-'
%left '*' '/'

%%

S : E '\n'
    {
        root = $1;
    }
    ;

E : E '+' T
    {
        $$ = createNode("+", $1, $3);
    }
    | E '-' T
    {
        $$ = createNode("-", $1, $3);
    }
    | T
    {
        $$ = $1;
    }
    ;

T : T '*' F
    {
        $$ = createNode("*", $1, $3);
    }
    | T '/' F
    {
        $$ = createNode("/", $1, $3);
    }
    | F
    {
        $$ = $1;
    }
    ;

F : '(' E ')'
    {
        $$ = $2;
    }
    | NUM
    {
        char temp[20];

        sprintf(temp, "%d", $1);

        $$ = createNode(temp, NULL, NULL);
    }
    ;

%%

struct node* createNode(char data[], struct node *left, struct node *right)
{
    struct node *temp;

    temp = (struct node*)malloc(sizeof(struct node));

    strcpy(temp->data, data);

    temp->left = left;
    temp->right = right;

    return temp;
}

void preorder(struct node *root)
{
    if(root != NULL)
    {
        printf("%s ", root->data);

        preorder(root->left);
        preorder(root->right);
    }
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

int main()
{
    printf("Enter expression: ");

    yyparse();

    printf("\nAbstract Syntax Tree (Preorder): ");
    preorder(root);

    printf("\n");

    return 0;
}
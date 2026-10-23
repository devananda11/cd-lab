#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("Rejected\n");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if(input[pos] == '+')
    {
        pos++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if(input[pos] == '*')
    {
        pos++;
        F();
        Tprime();
    }
}

void F()
{
    if(input[pos] == 'i')
    {
        pos++;
    }
    else if(input[pos] == '(')
    {
        pos++;

        E();

        if(input[pos] == ')')
            pos++;
        else
            error();
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%s", input);

    strcat(input, "$");

    E();

    if(input[pos] == '$')
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}






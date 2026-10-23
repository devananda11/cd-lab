
#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1, ip = 0;

void display(char action[])
{
    int i;

    printf("%-20s %-20s %-25s\n", "", "", "");

    for(i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("%*s", 20 - top - 1, "");
    printf("%-20s %-25s\n", input + ip, action);
}

int reduce()
{
    if(top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        display("Reduce: E -> i");
        return 1;
    }

    if(top >= 2 && stack[top-2] == 'E' &&
       stack[top-1] == '+' && stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce: E -> E+E");
        return 1;
    }

    if(top >= 2 && stack[top-2] == 'E' &&
       stack[top-1] == '-' && stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce: E -> E-E");
        return 1;
    }

    if(top >= 2 && stack[top-2] == 'E' &&
       stack[top-1] == '*' && stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce: E -> E*E");
        return 1;
    }

    if(top >= 2 && stack[top-2] == 'E' &&
       stack[top-1] == '/' && stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce: E -> E/E");
        return 1;
    }

    if(top >= 2 && stack[top-2] == '(' &&
       stack[top-1] == 'E' && stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        display("Reduce: E -> (E)");
        return 1;
    }

    return 0;
}

int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%99s", input);

    strcat(input, "$");

    printf("\n%-20s %-20s %-25s\n",
           "Stack", "Input", "Action");

    display("Start");

    while(1)
    {
        if(input[ip] != '$')
        {
            stack[++top] = input[ip++];
            display("Shift");
        }

        while(reduce());

        if(input[ip] == '$' && top == 0 && stack[top] == 'E')
        {
            display("Accept");
            break;
        }

        if(input[ip] == '$')
        {
            display("Reject");
            break;
        }
    }

    return 0;
}

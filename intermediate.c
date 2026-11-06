#include <stdio.h>
#include <ctype.h>
#include <string.h>

char stack[100][20];
int top = -1;
int tempCount = 1;

struct Quadruple
{
    char op[5];
    char arg1[20];
    char arg2[20];
    char result[20];
};

struct Quadruple quad[100];
int quadCount = 0;

void push(char *str)
{
    strcpy(stack[++top], str);
}

char* pop()
{
    return stack[top--];
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

void infixToPostfix(char infix[], char postfix[])
{
    char opStack[100];
    int opTop = -1;
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        if (ch == ' ')
            continue;

        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }
        else if (ch == '(')
        {
            opStack[++opTop] = ch;
        }
        else if (ch == ')')
        {
            while (opTop != -1 && opStack[opTop] != '(')
                postfix[j++] = opStack[opTop--];

            opTop--;
        }
        else
        {
            while (opTop != -1 &&
                   precedence(opStack[opTop]) >= precedence(ch))
            {
                postfix[j++] = opStack[opTop--];
            }

            opStack[++opTop] = ch;
        }
    }

    while (opTop != -1)
        postfix[j++] = opStack[opTop--];

    postfix[j] = '\0';
}

void generateTAC(char postfix[])
{
    int i;
    char localStack[100][20];
    int top = -1;

    char op1[20], op2[20], result[20];

    for (i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if (isalnum(ch))
        {
            localStack[++top][0] = ch;
            localStack[top][1] = '\0';
        }
        else
        {
            strcpy(op2, localStack[top--]);
            strcpy(op1, localStack[top--]);

            sprintf(result, "t%d", tempCount++);

            printf("%s = %s %c %s\n",
                   result, op1, ch, op2);

            quad[quadCount].op[0] = ch;
            quad[quadCount].op[1] = '\0';

            strcpy(quad[quadCount].arg1, op1);
            strcpy(quad[quadCount].arg2, op2);
            strcpy(quad[quadCount].result, result);

            quadCount++;
        }
    }
}

int main()
{
    char infix[100];
    char postfix[100];

    printf("Enter an arithmetic expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("\nPostfix Expression: %s\n", postfix);

    printf("\nThree Address Code:\n");
    generateTAC(postfix);

    printf("\nQuadruples:\n");
    printf("No.\tOp\tArg1\tArg2\tResult\n");

    for (int i = 0; i < quadCount; i++)
    {
        printf("%d\t%s\t%s\t%s\t%s\n",
               i,
               quad[i].op,
               quad[i].arg1,
               quad[i].arg2,
               quad[i].result);
    }

    return 0;
}

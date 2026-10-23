#include <stdio.h>
#include <string.h>

int main()
{
    int n, i;
    char line[100];

    printf("Enter number of Three Address Code instructions: ");
    scanf("%d", &n);
    getchar();

    printf("\nEnter Three Address Code:\n");

    for (i = 0; i < n; i++)
    {
        char result[20], op1[20], op2[20], op;

        fgets(line, sizeof(line), stdin);

        if (strstr(line, "goto") != NULL)
        {
            char label[20];

            sscanf(line, "goto %s", label);

            printf("JMP %s\n", label);
        }

        else if (sscanf(line, "%s = %s %c %s",
                        result, op1, &op, op2) == 4)
        {
            switch (op)
            {
                case '+':
                    printf("MOV AX, %s\n", op1);
                    printf("ADD AX, %s\n", op2);
                    printf("MOV %s, AX\n", result);
                    break;

                case '-':
                    printf("MOV AX, %s\n", op1);
                    printf("SUB AX, %s\n", op2);
                    printf("MOV %s, AX\n", result);
                    break;

                case '*':
                    printf("MOV AX, %s\n", op1);
                    printf("MOV BX, %s\n", op2);
                    printf("MUL BX\n");
                    printf("MOV %s, AX\n", result);
                    break;

                default:
                    printf("Unsupported operator\n");
            }
        }

        else if (sscanf(line, "%s = %s", result, op1) == 2)
        {
            printf("MOV AX, %s\n", op1);
            printf("MOV %s, AX\n", result);
        }
    }

    return 0;
}
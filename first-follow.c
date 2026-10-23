#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
char first[20][20], follow[20][20];

int n;
int fc[20], flc[20];

int isNT(char c)
{
    return c >= 'A' && c <= 'Z';
}

int indexOf(char c)
{
    int i;

    for(i = 0; i < n; i++)
        if(prod[i][0] == c)
            return i;

    return -1;
}

void addFirst(int i, char c)
{
    int j;

    for(j = 0; j < fc[i]; j++)
        if(first[i][j] == c)
            return;

    first[i][fc[i]++] = c;
}

void addFollow(int i, char c)
{
    int j;

    for(j = 0; j < flc[i]; j++)
        if(follow[i][j] == c)
            return;

    follow[i][flc[i]++] = c;
}

void findFirst(int i)
{
    int j, k, x;
    char *rhs = prod[i] + 2;

    for(j = 0; rhs[j] != '\0'; j++)
    {
        if(rhs[j] == '#')
        {
            addFirst(i, '#');
            return;
        }

        if(!isNT(rhs[j]))
        {
            addFirst(i, rhs[j]);
            return;
        }

        x = indexOf(rhs[j]);

        findFirst(x);

        for(k = 0; k < fc[x]; k++)
        {
            if(first[x][k] != '#')
                addFirst(i, first[x][k]);
        }

        int eps = 0;

        for(k = 0; k < fc[x]; k++)
        {
            if(first[x][k] == '#')
                eps = 1;
        }

        if(!eps)
            return;

        if(rhs[j + 1] == '\0')
            addFirst(i, '#');
    }
}

void findFollow(int i)
{
    int j, k, x, y;
    char A = prod[i][0];

    if(i == 0)
        addFollow(i, '$');

    for(x = 0; x < n; x++)
    {
        char *rhs = prod[x] + 2;

        for(j = 0; rhs[j] != '\0'; j++)
        {
            if(rhs[j] != A)
                continue;

            /* A is followed by a symbol */
            if(rhs[j + 1] != '\0')
            {
                char B = rhs[j + 1];

                if(!isNT(B))
                {
                    addFollow(i, B);
                }
                else
                {
                    y = indexOf(B);

                    for(k = 0; k < fc[y]; k++)
                    {
                        if(first[y][k] != '#')
                            addFollow(i, first[y][k]);
                    }

                    for(k = 0; k < fc[y]; k++)
                    {
                        if(first[y][k] == '#')
                        {
                            int lhs = indexOf(prod[x][0]);

                            if(lhs != i)
                            {
                                findFollow(lhs);

                                int z;

                                for(z = 0;
                                    z < flc[lhs];
                                    z++)
                                {
                                    addFollow(i,
                                              follow[lhs][z]);
                                }
                            }
                        }
                    }
                }
            }

            /* A is at the end */
            else
            {
                int lhs = indexOf(prod[x][0]);

                if(lhs != i)
                {
                    findFollow(lhs);

                    for(k = 0;
                         k < flc[lhs];
                         k++)
                    {
                        addFollow(i,
                                  follow[lhs][k]);
                    }
                }
            }
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (# for epsilon):\n");

    for(i = 0; i < n; i++)
        scanf("%s", prod[i]);

    /* Find FIRST */
    for(i = 0; i < n; i++)
        findFirst(i);

    printf("\nFIRST:\n");

    for(i = 0; i < n; i++)
    {
        printf("FIRST(%c) = { ",
               prod[i][0]);

        for(j = 0; j < fc[i]; j++)
            printf("%c ", first[i][j]);

        printf("}\n");
    }

    /* Find FOLLOW */
    for(i = 0; i < n; i++)
        findFollow(i);

    printf("\nFOLLOW:\n");

    for(i = 0; i < n; i++)
    {
        printf("FOLLOW(%c) = { ",
               prod[i][0]);

        for(j = 0; j < flc[i]; j++)
            printf("%c ", follow[i][j]);

        printf("}\n");
    }

    return 0;
}
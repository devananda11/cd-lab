
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
char nt[20];
char first[20][20], follow[20][20];

int n, m;
int fc[20], flc[20];

int isNT(char c)
{
    return c >= 'A' && c <= 'Z';
}

int indexOf(char c)
{
    int i;

    for(i = 0; i < m; i++)
        if(nt[i] == c)
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
    int j, k, x, p;
    char *rhs;

    for(p = 0; p < n; p++)
    {
        if(prod[p][0] != nt[i])
            continue;

        rhs = prod[p] + 2;

        for(j = 0; rhs[j] != '\0'; j++)
        {
            if(rhs[j] == '#')
            {
                addFirst(i, '#');
                break;
            }

            if(!isNT(rhs[j]))
            {
                addFirst(i, rhs[j]);
                break;
            }

            x = indexOf(rhs[j]);

            if(x == i)
                break;

            findFirst(x);

            for(k = 0; k < fc[x]; k++)
                if(first[x][k] != '#')
                    addFirst(i, first[x][k]);

            int eps = 0;

            for(k = 0; k < fc[x]; k++)
                if(first[x][k] == '#')
                    eps = 1;

            if(!eps)
                break;

            if(rhs[j + 1] == '\0')
                addFirst(i, '#');
        }
    }
}

void findFollow(int i)
{
    int j, k, x, y, p;
    char A = nt[i];

    if(i == 0)
        addFollow(i, '$');

    for(p = 0; p < n; p++)
    {
        char *rhs = prod[p] + 2;

        for(j = 0; rhs[j] != '\0'; j++)
        {
            if(rhs[j] != A)
                continue;

            if(rhs[j + 1] != '\0')
            {
                char B = rhs[j + 1];

                if(!isNT(B))
                    addFollow(i, B);
                else
                {
                    y = indexOf(B);

                    for(k = 0; k < fc[y]; k++)
                        if(first[y][k] != '#')
                            addFollow(i, first[y][k]);

                    for(k = 0; k < fc[y]; k++)
                    {
                        if(first[y][k] == '#')
                        {
                            int lhs = indexOf(prod[p][0]);

                            if(lhs != i)
                            {
                                findFollow(lhs);

                                int z;

                                for(z = 0; z < flc[lhs]; z++)
                                    addFollow(i, follow[lhs][z]);
                            }
                        }
                    }
                }
            }
            else
            {
                int lhs = indexOf(prod[p][0]);

                if(lhs != i)
                {
                    findFollow(lhs);

                    for(k = 0; k < flc[lhs]; k++)
                        addFollow(i, follow[lhs][k]);
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
    {
        scanf("%s", prod[i]);

        if(indexOf(prod[i][0]) == -1)
            nt[m++] = prod[i][0];
    }

    for(i = 0; i < m; i++)
        findFirst(i);

    printf("\nFIRST:\n");

    for(i = 0; i < m; i++)
    {
        printf("FIRST(%c) = { ", nt[i]);

        for(j = 0; j < fc[i]; j++)
            printf("%c ", first[i][j]);

        printf("}\n");
    }

    for(i = 0; i < m; i++)
        findFollow(i);

    printf("\nFOLLOW:\n");

    for(i = 0; i < m; i++)
    {
        printf("FOLLOW(%c) = { ", nt[i]);

        for(j = 0; j < flc[i]; j++)
            printf("%c ", follow[i][j]);

        printf("}\n");
    }

    return 0;
}

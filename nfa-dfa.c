
#include <stdio.h>

int n, m;
int nfa[20][20][20], count[20][20];
int dfa[100][20], states[100][20];
int d = 0;

int exists(int a[])
{
    for(int i = 0; i < d; i++)
    {
        int same = 1;

        for(int j = 0; j < n; j++)
            if(states[i][j] != a[j])
                same = 0;

        if(same)
            return i;
    }

    return -1;
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("Number of transitions from q%d on symbol %d: ", i, j);
            scanf("%d", &count[i][j]);

            printf("Enter next states: ");

            for(int k = 0; k < count[i][j]; k++)
            {
                int x;
                scanf("%d", &x);
                nfa[i][j][k] = x;
            }
        }
    }

    states[0][0] = 1;
    d = 1;

    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int temp[20] = {0};

            for(int k = 0; k < n; k++)
            {
                if(states[i][k] == 1)
                {
                    for(int l = 0; l < count[k][j]; l++)
                    {
                        int x = nfa[k][j][l];
                        temp[x] = 1;
                    }
                }
            }

            int pos = exists(temp);

            if(pos == -1)
            {
                for(int k = 0; k < n; k++)
                    states[d][k] = temp[k];

                pos = d;
                d++;
            }

            dfa[i][j] = pos;
        }
    }

    printf("\nDFA Transition Table\n");

    printf("State\t");
    for(int i = 0; i < m; i++)
        printf("%d\t", i);
    printf("\n");

    for(int i = 0; i < d; i++)
    {
        printf("{");

        for(int j = 0; j < n; j++)
            if(states[i][j])
                printf("q%d ", j);

        printf("}\t");

        for(int j = 0; j < m; j++)
            printf("%d\t", dfa[i][j]);

        printf("\n");
    }

    return 0;
}

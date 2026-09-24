#include <stdio.h>

#define MAX 20

int main()
{
    int n,m;

    printf("Enter number of states: ");
    scanf("%d",&n);

    printf("Enter number of symbols: ");
    scanf("%d",&m);

    int trans[MAX][MAX];

    printf("Enter transition table:\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%d",&trans[i][j]);

    int final[MAX];

    printf("Enter final states (1=Final, 0=Non-final):\n");
    for(int i=0;i<n;i++)
        scanf("%d",&final[i]);

    int group[MAX];

    // Initial partition
    for(int i=0;i<n;i++)
    {
        if(final[i])
            group[i]=1;
        else
            group[i]=0;
    }

    int changed=1;

    while(changed)
    {
        changed=0;

        int newGroup[MAX];
        int nextGroup=0;

        for(int i=0;i<n;i++)
        {
            int found=-1;

            for(int j=0;j<i;j++)
            {
                if(group[i]!=group[j])
                    continue;

                int same=1;

                for(int k=0;k<m;k++)
                {
                    if(group[trans[i][k]]!=group[trans[j][k]])
                    {
                        same=0;
                        break;
                    }
                }

                if(same)
                {
                    found=newGroup[j];
                    break;
                }
            }

            if(found==-1)
            {
                newGroup[i]=nextGroup++;
            }
            else
            {
                newGroup[i]=found;
            }
        }

        for(int i=0;i<n;i++)
        {
            if(group[i]!=newGroup[i])
                changed=1;

            group[i]=newGroup[i];
        }
    }

    printf("\nEquivalent State Groups:\n");

    int printed[MAX]={0};

    for(int i=0;i<n;i++)
    {
        if(printed[i])
            continue;

        printf("{ ");

        for(int j=i;j<n;j++)
        {
            if(group[i]==group[j])
            {
                printf("%d ",j);
                printed[j]=1;
            }
        }

        printf("}\n");
    }
    printf("\nMinimized DFA Transition Table\n\n");

    printf("State\t");
    for(int i=0;i<m;i++)
        printf("%d\t",i);
    printf("\n");

    int done[MAX]={0};

    for(int i=0;i<n;i++)
    {
        if(done[group[i]])
            continue;

        done[group[i]]=1;

        printf("G%d\t",group[i]);

        for(int j=0;j<m;j++)
        {
            int nextState = trans[i][j];
            printf("G%d\t",group[nextState]);
        }

        printf("\n");
    }
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX 20

int n, m;
char states[MAX];
char symbols[MAX];
int trans[MAX][MAX][MAX];      
int dfa[MAX][MAX];             
char dfaStates[MAX][MAX];      
int dfaCount = 0;

int exists(char set[])
{
    for(int i=0;i<dfaCount;i++)
    {
        if(strcmp(dfaStates[i], set)==0)
            return i;
    }
    return -1;
}

void sortSet(char s[])
{
    int len=strlen(s);

    for(int i=0;i<len-1;i++)
        for(int j=i+1;j<len;j++)
            if(s[i]>s[j])
            {
                char t=s[i];
                s[i]=s[j];
                s[j]=t;
            }
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d",&n);

    printf("Enter states:\n");
    for(int i=0;i<n;i++)
        scanf(" %c",&states[i]);

    printf("Enter number of symbols: ");
    scanf("%d",&m);

    printf("Enter symbols:\n");
    for(int i=0;i<m;i++)
        scanf(" %c",&symbols[i]);

    int t;
    printf("Enter number of transitions: ");
    scanf("%d",&t);

    memset(trans,0,sizeof(trans));

    printf("Enter transitions (From Symbol To):\n");

    for(int i=0;i<t;i++)
    {
        char from,to,sym;
        scanf(" %c %c %c",&from,&sym,&to);

        int f=-1,toIdx=-1,s=-1;

        for(int j=0;j<n;j++)
        {
            if(states[j]==from) f=j;
            if(states[j]==to) toIdx=j;
        }

        for(int j=0;j<m;j++)
            if(symbols[j]==sym)
                s=j;

        trans[f][s][toIdx]=1;
    }

    strcpy(dfaStates[0],"A");
    dfaCount=1;

    for(int curr=0;curr<dfaCount;curr++)
    {
        for(int sym=0;sym<m;sym++)
        {
            char newSet[MAX]="";

            for(int k=0;k<strlen(dfaStates[curr]);k++)
            {
                char st=dfaStates[curr][k];

                int idx=-1;

                for(int x=0;x<n;x++)
                    if(states[x]==st)
                        idx=x;

                for(int y=0;y<n;y++)
                {
                    if(trans[idx][sym][y])
                    {
                        if(strchr(newSet,states[y])==NULL)
                        {
                            int len=strlen(newSet);
                            newSet[len]=states[y];
                            newSet[len+1]='\0';
                        }
                    }
                }
            }

            sortSet(newSet);

            if(strlen(newSet)==0)
                strcpy(newSet,"-");

            int pos=exists(newSet);

            if(pos==-1)
            {
                strcpy(dfaStates[dfaCount],newSet);
                pos=dfaCount;
                dfaCount++;
            }

            dfa[curr][sym]=pos;
        }
    }

    printf("\nEquivalent DFA Transition Table\n\n");

    printf("State\t");

    for(int i=0;i<m;i++)
        printf("%c\t",symbols[i]);

    printf("\n");

    for(int i=0;i<dfaCount;i++)
    {
        printf("%s\t",dfaStates[i]);

        for(int j=0;j<m;j++)
            printf("%s\t",dfaStates[dfa[i][j]]);

        printf("\n");
    }

    return 0;
}

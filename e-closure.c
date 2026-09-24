#include <stdio.h>
#include <string.h>
#define MAX 20
char states[MAX][10];
char transFrom[MAX][10], transTo[MAX][10],transInput[MAX][10];
int transCount;
int visited[MAX];
int stateCount;

int getIndex(char state[]){
    for(int i=0;i<stateCount;i++){
        if (strcmp(states[i],state)==0){
            return i;
        }
    }
    return -1;
}
void epsilonClosure(char state[]){
    int idx=getIndex(state);
    if (idx==-1 || visited[idx]) return;
    visited[idx]=1;
    printf("%s ",state);
    for(int i=0;i<transCount;i++){
        if (strcmp(transFrom[i],state)==0 && 
            strcmp(transInput[i],"e")==0){
                epsilonClosure(transTo[i]);
            }
    }
}
int main()
{
    printf("Enter number of states: ");
    scanf("%d",&stateCount);

    printf("Enter state names:\n");
    for(int i=0;i<stateCount;i++)
        scanf("%s",states[i]);

    printf("Enter number of transitions: ");
    scanf("%d",&transCount);

    printf("Enter transitions (From Input To):\n");
    for(int i=0;i<transCount;i++)
    {
        scanf("%s %s %s",
              transFrom[i],
              transInput[i],
              transTo[i]);
    }

    printf("\nEpsilon Closures:\n");

    for(int i=0;i<stateCount;i++)
    {
        for(int j=0;j<stateCount;j++)
            visited[j]=0;


        printf("Ep-Closure(%s) = { ",states[i]);
        epsilonClosure(states[i]);
        printf("}\n");
    }

    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX 20

char states[MAX][10];
char symbols[MAX][10];
char from[MAX][10], input[MAX][10], to[MAX][10];

int stateCount, symbolCount, transCount;
int closure[MAX][MAX];
int visited[MAX];

int getIndex(char state[]) {
    for (int i = 0; i < stateCount; i++) {
        if (strcmp(states[i], state) == 0) {
            return i;
        }
    }
    return -1;
}
void dfs(char state[]){
    int idx=getIndex(state);
    if (visited[idx]) return;
    visited[idx]=1;
    closure[idx][idx]=1;
    for(int i=0;i<transCount;i++){
        if (strcmp(from[i],state)==0 && 
        strcmp(input[i],"e")==0){
            int next=getIndex(to[i]);
            closure[idx][next]=1;
            dfs(to[i]);
            for(int j=0;j<stateCount;j++){
                if (closure[next][j]){
                    closure[idx][j]=1;
                }
            }
        }
    }
}
int main() {

    printf("Enter number of states: ");
    scanf("%d", &stateCount);
    
    printf("Enter states:\n");
    for (int i = 0; i < stateCount; i++) {
        scanf("%s", states[i]);
    }

    printf("Enter number of input symbols (excluding e): ");
    scanf("%d", &symbolCount);
    
    printf("Enter input symbols:\n");
    for (int i = 0; i < symbolCount; i++) {
        scanf("%s", symbols[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &transCount);
    
    printf("Enter transitions (From Input To):\n");
    for (int i = 0; i < transCount; i++) {
        scanf("%s %s %s", from[i], input[i], to[i]);
    }

    for (int i = 0; i < stateCount; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(states[i]);
    }

    printf("\nEquivalent NFA without epsilon transitions:\n\n");
    for (int i = 0; i < stateCount; i++) {
    for (int j = 0; j < symbolCount; j++) {

        int printed[MAX] = {0};   
        printf("%s --%s--> { ", states[i], symbols[j]);

        for (int k = 0; k < stateCount; k++) {

            if (!closure[i][k])
                continue;

            for (int t = 0; t < transCount; t++) {

                if (strcmp(from[t], states[k]) == 0 &&
                    strcmp(input[t], symbols[j]) == 0) {

                    int dest = getIndex(to[t]);

                    for (int x = 0; x < stateCount; x++) {

                        if (closure[dest][x] && !printed[x]) {
                            printf("%s ", states[x]);
                            printed[x] = 1;
                        }
                    }
                }
            }
        }

        printf("}\n");
    }
}
    
    return 0;
}
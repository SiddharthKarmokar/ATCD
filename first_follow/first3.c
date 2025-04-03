#include<stdio.h>
#include<string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10


char firstsets[MAX_SYMBOLS][MAX_SYMBOLS];
char nonTerminals[MAX_RULES];
char rhs[MAX_RULES][MAX_SYMBOLS][MAX_RULES];
int numRules;

int isnonTerminal(char symbol){
    return (symbol >= 'A' && symbol <= 'Z');
}

void addFirst(int index, char symbol){
    for(int i = 0; firstsets[index][i] != '\0'; i++){
        if(firstsets[index][i] == symbol) return;
    }
    int len = strlen(firstsets[index]);
    firstsets[index][len] = symbol;
    firstsets[index][len + 1] = '\0';
}

void findFirst(int index){
    for(int i = 0; rhs[index][i][0] != '\0'; i++){
        char *productions = rhs[index][i];
        int allEpsilon = 1;
        for(int j = 0; productions[j]!= '\0'; j++){
            char current = productions[j];

            if(!isnonTerminal(current)){
                addFirst(index, current);
                allEpsilon = 0;
                break;
            }else{
                int epsilon = 0;
                for(int k = 0; k < numRules; k++){
                    if(nonTerminals[k] == current){
                        findFirst(k);
                        for(int m = 0; firstsets[k][m] != '\0'; m++){
                            if(firstsets[k][m] == 'e'){
                                epsilon = 1;
                            }else{
                                addFirst(index, firstsets[k][m]);
                            }
                        }
                    }
                }

                if(!epsilon){
                    allEpsilon = 0;
                    break;
                }
            }
        }
        if(allEpsilon){
            addFirst(index, 'e');
        }
    }
}


int main(){
    FILE *file = fopen("in.txt", "r");
    fscanf(file, "%d", &numRules);
    getc(file);
    // printf("Working?\n");
    for(int i = 0; i < numRules; i++){
        char input[MAX_SYMBOLS*2];
        fgets(input, sizeof(input), file);
        input[strcspn(input, "\n")] = '\0';
        nonTerminals[i] = input[0];
        int i1 = 0, i2 = 0;
        for(int j = 3; input[j] != '\0'; j++){
            if(input[j] == ' '){
                continue;
            }
            if(input[j] == '|'){
                rhs[i][i1][i2] = '\0';
                i1++;
                i2 = 0;
            }else{
                rhs[i][i1][i2++] = input[j];
            }
        }
        rhs[i][i1][i2] = '\0';
    }

    for(int i = 0; i < numRules; i++){
        findFirst(i);
    }

    for(int i = 0; i < numRules; i++){
        printf("%s\n", firstsets[i]);
    }
    fclose(file);
    return 0;
}
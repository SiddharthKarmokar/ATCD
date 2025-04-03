#include<stdio.h>
#include<string.h>
#include<stdbool.h>


char nonterminal[10];
char rhs[10][10][10];
char first[10][10];
char follow[10][10];
int n;

void addfollow(int index, char symbol){

    for(int i = 0; follow[index][i] != '\0'; i++){
        if(follow[index][i] == symbol)return;
    }
    int len = strlen(follow[index]);
    follow[index][len] = symbol;
    follow[index][len + 1] = '\0';
}

int isnonterminal(char symbol){
    return (symbol >= 'A' && symbol <= 'Z');
}

void findFollow(int n){
    addfollow(0, '$');

    int change = 1;
    while(change){
        change = 0;
        for(int i = 0; i < n; i++){
            char lhs = nonterminal[i];
            for(int j = 0; rhs[i][j][0] != '\0'; j++){
                char *prod = rhs[i][j];

                for(int k = 0; prod[k] != '\0'; k++){
                    char curr = prod[k];

                    if(isnonterminal(curr)){
                        int curidx = -1;
                        for(int m = 0; m < n; m++){
                            if(nonterminal[m] == curr){
                                curidx = m;
                                break;
                            }
                        }
                        if(prod[k+1] != '\0'){
                            char next = prod[k + 1];
                            if(!isnonterminal(next)){
                                if(!strchr(follow[curidx], next)){
                                    addfollow(curidx, next);
                                    change = 1;
                                }
                            }else{
                                int nextidx = -1;
                                for(int m = 0; m < n; m++){
                                    if(nonterminal[m] == next){
                                        nextidx = m;
                                        break;
                                    }
                                }

                                for(int m = 0; first[nextidx][m] != '\0'; m++){
                                    if(first[nextidx][m] != 'e' && !strchr(follow[curidx], first[nextidx][m])){
                                        addfollow(curidx, first[nextidx][m]);
                                        change = 1;
                                    }
                                }

                                if(strchr(first[nextidx], 'e')){
                                    for(int m = 0; follow[i][m]; m++){
                                        if(!strchr(follow[curidx], follow[i][m])){
                                            addfollow(curidx, follow[i][m]);
                                            change = 1;
                                        }
                                    }
                                }
                            }
                        }else{
                            for(int m = 0; follow[i][m] != '\0'; m++){
                                if(!strchr(follow[curidx], follow[i][m])){
                                    addfollow(curidx, follow[i][m]);
                                    change = 1;
                                }
                            }
                        }

                    }
                }
            }
        }
    }
}

void addFirst(int index, char symbol){
    if(!strchr(first[index], symbol)){
        int len = strlen(first[index]);
        first[index][len] = symbol;
        first[index][len + 1]= '\0';
    }
}

void findFirst(int index){
    for(int i = 0; rhs[index][i][0] != '\0'; i++){
        char *prod = rhs[index][i];
        int allEpsilon = 1;
        for(int j = 0; prod[j] != '\0'; j++){
            char curr = prod[j];
            if(!isnonterminal(curr)){
                addFirst(index, curr);
                allEpsilon = 0;
                break;
            }else{
                int epsilon = 0;
                for(int k = 0; k < n; k++){
                    if(nonterminal[k] == curr){
                        findFirst(k);
                        for(int m = 0; first[k][m] != '\0'; m++){
                            if(first[k][m] == 'e'){
                                epsilon = 1;
                            }else{
                                addFirst(index, first[k][m]);
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
    fscanf(file, "%d", &n);
    getc(file);

    for(int i = 0; i < n; i++){
        char input[20];
        fgets(input, sizeof(input), file);
        input[strcspn(input, "\n")] = '\0';
        nonterminal[i] = input[0];

        int rhsidx = 0, symidx = 0;
        for(int j = 3; input[j] != '\0'; j++){
            if(input[j] == ' '){
                continue;
            }
            if(input[j] == '|'){
                rhs[i][rhsidx][symidx] = '\0';
                rhsidx++;
                symidx = 0;
            }else{
                rhs[i][rhsidx][symidx++] = input[j];
            }
        }
        rhs[i][rhsidx][symidx] = '\0';
    }
    for(int i = 0; i < n; i++){
        findFirst(i);
    }
    findFollow(n);
    for(int i = 0; i < n; i++){
        printf("%s\n", follow[i]);
    }

    fclose(file);
}

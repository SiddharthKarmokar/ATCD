#include<string.h>
#include<stdio.h>
#include<stdbool.h>

int num;
typedef struct {
    char left;
    char right[50];
} Prod;

bool isnonterminal(char sym){
    return (sym >= 'A' && sym <= 'Z');
}
char trail[26][50] = { {0}};
void addTrail(int index, char symbol){
    if(strchr(trail[index], symbol))return;
    int len = strlen(trail[index]);
    trail[index][len] = symbol;
    trail[index][len + 1] = '\0';
}


int main(){
    Prod p[50];
    int count = 0;
    scanf("%d", &num);
    for(int i = 0; i < num; i++){
        char input[100];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        char left = input[0];
        char temp[50];
        int pos = 0;
        char *arrow = strstr(input, "->");
        arrow += 2;
        char *token = strtok(NULL, "|");
        while(token != NULL){
            p[count].left = left;
            strcpy(p[count].right, token);
            count++;
            token = strtok(NULL, "|");
        }
    }
    bool change;
    bool null[26] = { false };
    do{
        change = false;
        for(int i = 0; i < count; i++){
            int l = p[i].left - 'A';
            if(null[l]){
                continue;
            }
            if(strcmp(p[i].right, "e") == 0){
                null[l] = true;
                change = true;
                continue;
            }

            bool isallnull = true;
            for(int j = 0; j < strlen(p[i].right); j++){
                char c = p[i].right[j];
                if(c >= 'A' && c <= 'Z'){
                    if(!null[c - 'A']){
                        isallnull = false;
                        break;
                    }
                }else{
                    isallnull = false;
                    break;
                }
            }
            if(isallnull){
                null[l] = true;
                change = true;
            }
        }
    }while(change);

    do{
        change = false;
        for(int i = 0; i < count; i++){
            int l = p[i].left  - 'A';
            if(strcmp(p[i].right, "e") == 0){
                continue;
            }
            for(int j = strlen(p[i].right) - 1; j >= 0; j--){
                char c = p[i].right[j];
                if(!isnonterminal(c)){
                    addTrail(l, c);
                }else{
                    int idx = c - 'A';
                    for(int k = 0; trail[idx][k] != '\0'; k++){
                        char t = trail[idx][k];
                        if(!strchr(trail[l], t)){
                            addTrail(l, t);
                            change = true;
                        }
                    }
                    if(!null[idx]){
                        break;
                    }
                }
            }
        }
    }while(change);

    bool printed[26] = {false};
    for(int i = 0; i < count; i++){
        printed[p[i].left - 'A'] = true;
    }

    for(int i = 0; i < 26; i++){
        if(printed[i]){
            printf("%s\n", trail[i]);
        }
    }

    return 0;
}
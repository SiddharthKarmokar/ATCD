#include<stdio.h>
#include<string.h>

enum State { INITIAL, FINAL, q1 };

void processString(char *s){
    int i = 0;
    enum State curr = INITIAL;
    while(s[i] != '\0'){
        char c = s[i];
        switch(c){
            case '0':
                curr = q1;
                break;
            case '1':
                if(curr == q1){
                    curr = FINAL;
                }else if(curr == INITIAL){
                    curr = INITIAL;
                }else{
                    curr = INITIAL;
                }
                break;
        }
        i++;
    }
    if(curr == INITIAL){
        printf("Rejected\n");
    }else{
        printf("Accepted\n");
    }
}


int main(){
    char input[100];
    fgets(input, sizeof(input), stdin);
    // fprintf(stderr, "working\n");
    size_t len = strlen(input);
    if(len > 0 && input[len - 1] == '\n'){
        input[len - 1] = '\0';
    }
    processString(input);
    return 0;
}

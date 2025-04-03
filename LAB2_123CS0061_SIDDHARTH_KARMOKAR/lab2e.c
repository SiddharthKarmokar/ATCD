#include<stdio.h>
// #include<string.h>

enum State { INITIAL, A, B, DEAD};

void processString(char *s){
    enum State state = INITIAL;
    int i = 0;

    while(s[i] != '\0'){
        char c = s[i];
        switch(state){
            case INITIAL:
                if(c == '0'){
                    state = A;
                }else if(c == '1'){
                    state = B;
                }else if(c == '\n'){
                    printf("ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case A:
                if(c == '0'){
                    state = DEAD;
                }else if(c == '1'){
                    state = INITIAL;
                }else if(c == '\n'){
                    printf("ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case B:
                if(c == '0'){
                    state = INITIAL;
                }else if(c == '1'){
                    state = DEAD;
                }else if(c == '\n'){
                    printf("ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case DEAD:
                if(c == '\n'){
                    printf("NOT ACCEPTED\n");
                    return;
                }
                break;
        }
        i++;
    }

    return;
}


int main(){
    char input[100];

    printf("Enter String:\n");
    fgets(input, sizeof(input), stdin);

    processString(input);

    return 0;
}
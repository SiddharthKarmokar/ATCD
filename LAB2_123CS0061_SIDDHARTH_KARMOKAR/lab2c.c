#include<stdio.h>
// #include<string.h>

enum State { INITIAL, A, B, C, DEAD};

void processString(char *s){
    enum State state = INITIAL;
    int i = 0;

    while(s[i] != '\0'){
        char c = s[i];
        switch(state){
            case INITIAL:
                if(c == 'a'){
                    state = A;
                }else if(c == 'b'){
                    state = INITIAL;
                }else if(c == '\n'){
                    printf("NOT ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case A:
                if(c == 'a'){
                    state = A;
                }else if(c == 'b'){
                    state = B;
                }else if(c == '\n'){
                    printf("NOT ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case B:
                if(c == 'a'){
                    state = A;
                }else if(c == 'b'){
                    state = C;
                }else if(c == '\n'){
                    printf("NOT ACCEPTED\n");
                    return;
                }else{
                    state = DEAD;
                }
                break;
            case C:
                if(c == 'a'){
                    state = C;
                }else if(c == 'b'){
                    state = C;
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

    if(state == A || state == B || state == DEAD){
        printf("NOT ACCEPTED\n");
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
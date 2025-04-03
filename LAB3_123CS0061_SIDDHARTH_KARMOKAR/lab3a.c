#include<stdio.h>
#include<string.h>
enum STATE{INITIAL, A, B, C, FINAL};

void solve(char *str){
    enum STATE curr = INITIAL;
    for(int i = 0; i < strlen(str); i++){
        char ch = str[i];
        switch(curr){
            case INITIAL:
                switch(ch){
                    case '/':
                        curr = A;
                        break;
                    default:
                        break;
                }
                break;
            case A:
                switch (ch) {
                    case '/':
                        curr = FINAL;
                        break;
                    case '*':
                        curr = B;
                        break;
                    default:
                        curr = INITIAL;
                        break;
                }
                break;
            case B:
                switch (ch) {
                    case '*':
                        curr = C;
                        break;
                    default:
                        curr = B;
                        break;
                }
                break;
            case C:
                switch (ch) {
                    case '/':
                        curr = FINAL;
                        break;
                    default:
                        curr = B;
                        break;
                }
                break;
            case FINAL:
                break;
            default:
                break;
        }
    }   
    if(curr == INITIAL || curr == A || curr == B || curr == C ){
        printf("This is not a comment line\n");
        return;
    }
    else{
        printf("This is a comment line\n");
        return;
    }
}

int main(){
    for(;;){
        printf("Enter a line in c: \n");
        char str[100];
        //scanf("%s", str);
        fgets(str, sizeof(str), stdin);
        solve(str);
    }
    return 0;
}
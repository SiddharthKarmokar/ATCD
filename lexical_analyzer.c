#include<stdio.h>
#include<ctype.h>
#include<string.h>

void classify(char *input){
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == ' '){
            continue;
        }
        else{
            if(isdigit(input[i])){
                printf("Digit: %c\n", input[i]);
            }else if(isalpha(input[i])){
                printf("Alphabet: %c\n", input[i]);
            }else if (strchr("+-*=<>/!", input[i])) {
                printf("Operator: %c\n", input[i]);
            }else if(ispunct(input[i])){
                printf("Punctuation: %c\n", input[i]);
            }else{
                printf("Unknown: %c\n", input[i]);
            }
        }
    }
    return;
}

int main(){
    char input[100];
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if(len > 0 && input[len-1] == '\n'){
        input[len - 1] = '\0';
    }
    classify(input);
    
    return 0;
}
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 100

const char *keywords[] = {"int", "float", "#", "include","main","if", "else", "while", "for", "return", "double", "break", "continue", "switch", "case", "default", "void"};
const int num_key = sizeof(keywords)/sizeof(keywords[0]);

const char *operators[] = {"+", "-", "/", "*", "/", "=", "&",">", "<", "*", "(", ")", "==", ">=", "<=", "&&", "||", "!", "++", "--"};
const int num_ops = sizeof(operators)/sizeof(operators[0]);

int isKeyword(char *word){
    for(int i = 0; i < num_key; i++){
        if(strcmp(word, keywords[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isOperator(char *word){
    for(int i = 0; i < num_ops; i++){
        if(strcmp(word, operators[i]) == 0){
            return 1;
        }
    }
    return 0;
}

int isIdentifier(char *word){
    if (isKeyword(word)) return 0;
    if ((isalpha(word[0])) || word[0] == '_'){
        for(int i = 0; word[i] != '\0'; i++){
            if(!isalnum(word[i]) && word[i] != '_'){
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

int isNumber(char *word){
    for(int i = 0; word[i] != '\0'; i++){
        if(!isdigit(word[i])){
            return 0;
        }
    }
    return 1;
}

int main(){
    // FILE * file = fopen("in.txt", "r");
    FILE * file = stdin;
    char ch, buffer[MAX];
    int i = 0;
    while(((ch = fgetc(file))) != EOF){
        if(ch == '"'){
            ch = fgetc(file);
            while(ch != '"' && ( ch != EOF ) ){
                ch = fgetc(file);
            }
        }
        if(ch == EOF){
            break;
        }
        if(isalnum(ch)){//112121+ buffer = [1, 1, 2, ..] == buffer = "112121"
            buffer[i++] = ch;
        }else{
            if(i != 0){
                buffer[i] = '\0';
                if (isKeyword(buffer)){
                    printf("Keyword: %s\n", buffer);
                } else if(isIdentifier(buffer)){
                    printf("Identifier: %s\n", buffer);
                }else if(isNumber(buffer)){
                    printf("Number: %s\n", buffer);
                }
                i = 0;
            }

            char op[3] = {ch, fgetc(file), '\0'};
            if(isOperator(op)){
                printf("Operator: %s\n", op);
            }else{
                ungetc(op[1], file);
                op[1] = '\0';
                if(isOperator(op)){
                    printf("Operator: %s\n", op);
                }
            }
        }
    }
    fclose(file);
    return 0;
}
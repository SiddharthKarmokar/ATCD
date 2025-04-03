#include<stdio.h>
#include<string.h>

int main(){

    char input[100];
    fgets(input, sizeof(input), stdin);
    int n = 0;    
    for(int i = 0; i < strlen(input); i++){
        if(input[i] == 'a'){
            n++;
        }else if(input[i] == 'b'){
            n--;
        }
    }

    if(n == 0){
        printf("Accepted\n");
    }else{
        printf("Rejected\n");
    }
    return 0;
}
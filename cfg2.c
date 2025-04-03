#include<stdio.h>
#include<string.h>
#define MAX 100

int solve(char *temp, char *string, char *arr[MAX], int index){
    if(strlen(temp) > strlen(string)){return 0;}
    if(strlen(temp) < strlen(string)){goto nxt;}
    for(int i = 0; i < strlen(string); i++){
        if(temp[i] != string[i]){
            return 0;
        }
    }
    return 1;
    nxt:
    for(int i = 0; i < index; i++){
        temp[size] = ;
    }

}


int main(){
    FILE* f = fopen("in.txt", "r");
    char *arr[MAX];
    char buffer[MAX];
    int index = 0;
    while(fgets(buffer, sizeof(buffer), f) && index < MAX){
        buffer[strcspn(buffer, "\n")] = '\0';
        arr[index] = strdup(buffer);
        index++;
    }
    char string[MAX];
    fgets(string, sizeof(string), f);
    char temp[MAX];
    int res = 0;
    for(int i = 0; i < index + 1; i++){
        res = res | solve(temp, string, arr, i, index);
    }
    return 0;
}
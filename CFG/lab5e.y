%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(const char* s);
%}

%token ZERO ONE NL

%%

s1: s2 NL {}; 

s2: ZERO {}
  | ONE {}
  | ZERO ZERO {}
  | ONE ONE {}
  | ZERO s2 ZERO {}
  | ONE s2 ONE {}
  ; 

%%

int flag;
int main(){
    flag = 1;
    printf("Enter the Expression (only as and bs):\n");
    yyparse();
    if(flag == 1){
        printf("Expression is a valid palindrome\n");
    }
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr, "Expression is not a valid palindrome\n");
    flag = 0;
}

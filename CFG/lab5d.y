%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(const char* s);
%}

%token ZERO ONE NL

%%
s1: s2 n1{};

s2: ZERO s2 ONE ONE{}
  | ZERO ONE ONE{}
  ; 

n1: NL {return 0;}
%%

int flag;

int main(){
    flag = 0;
    printf("Enter the expression(in a and b)\n");
    yyparse();
    if(flag == 0){
        printf("Expression is a valid a^nb^2n\n");
    }
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr, "Expression is not a valid a^nb^2n\n");
    flag = 1;
}
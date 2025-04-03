%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
void yyerror(const char* s);
%}

%token ZERO ONE NL

%%
s1: s2 n1{};

s2:ZERO ONE
  | ZERO ONE s2 
  ;

n1: NL {return 0;}
%%
int flag;
int main(){
    flag = 1;
    printf("Enter the Expression(in a and b)\n");
    yyparse();
    if(flag == 1){
        printf("Expression is a valid (ab)^n\n");
    }
    return 0;
}



void yyerror(const char* s){
    fprintf(stderr, "Expression is not a valid (ab)^n\n");
    flag = 0;
} 
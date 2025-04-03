%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int yylex();
void yyerror(const char* s);
%}

%union {
    char vname[10];
    int val;
}

%left '+' '-'
%left '*' '/'

%token <vname> NAME
%token <val> NUMBER
%type <val> expression

%%
input : line '\n' input
      | '\n' input
      |
      ;

line  : NAME '=' expression {
    printf("MOV %s, AX\n", $1);
}
expression  : NAME '+' NAME {
    printf("MOV AX, %s\n", $1);
    printf("ADD AX, %s\n", $3);
}
            | NAME '-' NAME { 
    printf("MOV AX, %s\n", $1);
    printf("SUB AX, %s\n", $3);
}
            | NAME '*' NAME { 
    printf("MOV AX, %s\n", $1);
    printf("MUL %s\n", $3);
}
            | NAME '/' NAME { 
    printf("MOV AX, %s\n", $1);
    printf("DIV %s\n", $3);
}
            | NUMBER {
    printf("MOV AX, %d\n", $1);
}
%%

int main(){
    printf("Enter the expression to generate assembly: \n");
    yyparse();
    return 0;
}

void yyerror(const char* s){
    fprintf(stderr, "Expression is not valid\n");
}

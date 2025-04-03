%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

extern FILE *yyin;
extern FILE *yyout;

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
    fprintf(yyout, "MOV %s, AX\n", $1);
}
expression  : NAME '+' NAME {
    fprintf(yyout, "MOV AX, %s\n", $1);
    fprintf(yyout, "ADD AX, %s\n", $3);
}
            | NAME '-' NAME { 
    fprintf(yyout, "MOV AX, %s\n", $1);
    fprintf(yyout, "SUB AX, %s\n", $3);
}
            | NAME '*' NAME { 
    fprintf(yyout, "MOV AX, %s\n", $1);
    fprintf(yyout, "MUL %s\n", $3);
}
            | NAME '/' NAME { 
    fprintf(yyout, "MOV AX, %s\n", $1);
    fprintf(yyout, "DIV %s\n", $3);
}
            | NUMBER {
    fprintf(yyout, "MOV AX, %d\n", $1);
}
%%

int main() {
    FILE *file = fopen("input.txt", "r");
    FILE *ofile = fopen("output.txt", "w");
    if ( (!file) || (!file) ) {
        perror("Failed to open input file");
        return 1;
    }
    
    yyin = file; 
    yyout = ofile; 
    printf("Reading from file input.txt\n");
    yyparse();
    printf("Written to output.txt\n");
    fclose(file);
    fclose(ofile);
    return 0;
}

void yyerror(const char* s){
    /* fprintf(stderr, "Expression is not valid\n"); */
}

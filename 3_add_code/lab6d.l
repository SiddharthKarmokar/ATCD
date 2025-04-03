%{
#include<stdio.h>
#include<string.h>
#include "lab6e.tab.h"
int yywrap();
// void yyerror(const char* s);
%}
 /* MOV a, b */
%%
[a-zA-Z][a-zA-Z0-9]* { strcpy(yylval.vname, yytext); return NAME; }
[=\n] { return yytext[0]; }
[+\-*/] { return yytext[0]; }
[\t] ;
. { printf("\nInvalid Character: %c\n", yytext[0]); }
%%
#ifndef LEX_MAIN
int main(){
    extern FILE *yyin, *yyout;
    yyin = fopen("input.txt", "r");
    yyout = fopen("output.txt", "w");
    yylex();
}
#endif

int yywrap(){
    return 1;
}

// void yyerror(const char* s){
//     printf("Error:\n%s", s);
// }

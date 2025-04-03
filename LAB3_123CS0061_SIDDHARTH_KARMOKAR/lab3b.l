%{
#include<stdio.h>
int yywrap(){return 1;}    
%}

%s A B C FINAL

%%

<INITIAL>"/" {BEGIN(A);}
<INITIAL>[^/\n] {BEGIN(INITIAL);}
<INITIAL>\n {BEGIN(INITIAL); printf("This line is not a comment line.\n");}

<A>"/" {BEGIN(FINAL);}
<A>"*" {BEGIN(B);}
<A>[^/*\n] {BEGIN(INITIAL);}
<A>\n {BEGIN(INITIAL); printf("This line is not a comment line.\n");}

<B>"*" {BEGIN(C);}
<B>[^*\n] {BEGIN(B);}
<B>\n {BEGIN(INITIAL);printf("This line is not a comment line.\n");}

<C>"/" {BEGIN(FINAL);}
<C>[^/\n] {BEGIN(B);}
<C>\n {BEGIN(INITIAL); printf("This line is not a comment line.\n");}

<FINAL>[^\n] {BEGIN(FINAL);}
<FINAL>\n {BEGIN(INITIAL); printf("This line is a comment line.\n");}

%%

int main(){
    printf("Enter a line in c: \n");
    yylex();
    return 0;
}
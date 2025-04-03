%{
#include<stdio.h>
int yywrap(){return 1;}
%}

%s A B C DEAD

%%

<INITIAL>a         { BEGIN(A); }
<INITIAL>b         { BEGIN(INITIAL); }
<INITIAL>[^ab\n]   { BEGIN(DEAD); }
<INITIAL>\n        { BEGIN(INITIAL); printf("NOT ACCEPTED\n"); }

<A>a               { BEGIN(A); }
<A>b               { BEGIN(B); }
<A>[^ab\n]         { BEGIN(DEAD); }
<A>\n              { BEGIN(INITIAL); printf("NOT ACCEPTED\n"); }

<B>a               { BEGIN(A); }
<B>b               { BEGIN(C); }
<B>[^ab\n]         { BEGIN(DEAD); }
<B>\n              { BEGIN(INITIAL); printf("NOT ACCEPTED\n"); }

<C>a               { BEGIN(C); }
<C>b               { BEGIN(C); }
<C>[^ab\n]         { BEGIN(DEAD); }
<C>\n              { BEGIN(INITIAL); printf("ACCEPTED\n"); }

<DEAD>[^\n]        { /* Stay in Dead*/ }
<DEAD>\n           { BEGIN(INITIAL); printf("INVALID\n"); }

%%

int yylex(void);

int main(){
    printf("Enter String\n");
    yylex();
    return 0;
}
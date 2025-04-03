%{
#include<stdio.h>
int yywrap(){return 1;}
%}

%s A B DEAD

%%

<INITIAL>0       { BEGIN(A); }
<INITIAL>1       { BEGIN(B); }
<INITIAL>[^10\n] { BEGIN(DEAD); }
<INITIAL>\n      { BEGIN(INITIAL); printf("ACCEPTED\n"); }

<A>0       { BEGIN(DEAD); }
<A>1       { BEGIN(B); }
<A>[^10\n] { BEGIN(DEAD); }
<A>\n      { BEGIN(INITIAL); printf("ACCEPTED\n"); }

<B>0       { BEGIN(A); }
<B>1       { BEGIN(DEAD); }
<B>[^10\n] { BEGIN(DEAD); }
<B>\n      { BEGIN(INITIAL); printf("ACCEPTED\n"); }


<DEAD>[^\n]       { BEGIN(DEAD); }
<DEAD>\n      {BEGIN(INITIAL); printf("NOT ACCEPTED\n");}

%%

int yylex(void);

int main(){
    printf("Enter String\n");
    yylex();
    return 0;
}
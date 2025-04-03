%{
#include <stdio.h>
%}

%token ID PLUS

%start E

%%
E : > T + E  { printf("E  -> > T + E \n"); } |  E { printf("E  ->  E\n"); } ;
T : > id { printf("T  -> > id\n"); } ;
%%

%{
#include <stdio.h>
#include "parser.tab.h"
%}

%option noyywrap

ID [a-zA-Z_][a-zA-Z0-9_]*
"+" { return PLUS; }
[ 	
] ;
. { printf("Invalid character: %s\n", yytext); }

%%

%{
#include "parser.tab.h"
%}

%%

id    return ID;
\+    return PLUS;
[ \t\n] ;
.    { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

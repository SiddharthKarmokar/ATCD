%{
#include "lab4b.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+   { yylval = atoi(yytext); return NUMBER; }
[ \t]+   ;  /* Ignore spaces and tabs */
\n       { return EOL; }

"+"      { return '+'; }
"-"      { return '-'; }
"*"      { return '*'; }
"/"      { return '/'; }
"("      { return '('; }
")"      { return ')'; }

.        { /* Ignore unrecognized characters */ }

%%

int yywrap() {
    return 1;
}

%{
#include "lab5b.tab.h"
#include "lab5c.tab.h"
#include "lab5d.tab.h"
#include "lab5e.tab.h"
#include<stdio.h>
%}

%%
[ \t]+   ;  /* Ignore spaces and tabs */
"\n"       { return NL; }
"a"      {return ZERO;}
"b"      {return ONE;}

.        {/* Ignores unrecognized characters */}
%%

int yywrap(){
    return 1;
}
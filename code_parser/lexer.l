%{
#include "parser.tab.h"
%}

DIGIT    [0-9]
LETTER   [a-zA-Z_]
ID       {LETTER}({LETTER}|{DIGIT})*

%%

"int"    { return INT; }
"float"  { return FLOAT; }
"char"   { return CHAR; }
"double" { return DOUBLE; }
"{"      { return LBRACE; }
"}"      { return RBRACE; }
";"      { return SEMICOLON; }
"="      { return ASSIGN; }

{ID}     { yylval.str = strdup(yytext); return IDENTIFIER; }
[0-9]+             { yylval.str = strdup(yytext); return NUMBER; }
[0-9]*"."[0-9]+    { yylval.str = strdup(yytext); return FLOAT; }

"#include"[ \t]*"<"{LETTER}({LETTER}|{DIGIT}|[/.])*">" { return INCLUDE; }

\n       { yylineno++; }
[ \t]+   ;  // Ignore whitespace

.        { return yytext[0]; }

%%

int yywrap() {
    return 1;
}

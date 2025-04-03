%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char *s);
    int yylex();
%}

%token ID PLUS

%%

E: T PLUS E { printf("E -> T + E\n"); }
 | T        { printf("E -> T\n"); }
 ;

T: ID       { printf("T -> id\n"); }
 ;

%%


void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\\n", s);
}

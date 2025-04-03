#include <stdio.h>

extern int yyparse();

int main() {
    printf("Parsing input:\n");
    yyparse();
    return 0;
}
//gcc -o slr_parser parser.tab.c lex.yy.c main.c -ll
#include <stdio.h>

extern int yyparse();

int main() {
    printf("Parsing input:\n");
    yyparse();
    return 0;
}

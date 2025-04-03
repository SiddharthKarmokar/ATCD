%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sym_tab.h"

extern int yylineno;  // Declare yylineno from lexer

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* msg) {
    fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
}
%}


/* Define a union for storing values */
%union {
    char* str;
}

/* Token definitions */
%token <str> INT FLOAT CHAR DOUBLE IDENTIFIER NUMBER
%token LBRACE RBRACE SEMICOLON ASSIGN
%token INCLUDE HEADER_FILE
%token RETURN
// '=' operator


/* Non-terminal types */
%type <str> type
%type <str> declaration

%%

/* program:
    declarations { display_sym_tab(); }
    ; */
program:
    includes declarations functions
    ;

declarations:
    declaration declarations
    | /* empty */
    ;

/* declaration:
    type IDENTIFIER SEMICOLON {
        insert_symbol($2, $1, size($1), yylineno, "global", "-");
    }
    | type IDENTIFIER ASSIGN NUMBER SEMICOLON {
        insert_symbol($2, $1, size($1), yylineno, "global", $4);
    }
    | type IDENTIFIER ASSIGN FLOAT SEMICOLON {
        insert_symbol($2, $1, size($1), yylineno, "global", $4);
    }
    ; */

declaration:
    type IDENTIFIER SEMICOLON {
        insert_symbol($2, $1, size($1), yylineno, "global", "-");
    }
    | type IDENTIFIER ASSIGN NUMBER SEMICOLON {
        insert_symbol($2, $1, size($1), yylineno, "global", $4);
    }
    | type IDENTIFIER '[' NUMBER ']' SEMICOLON {
        insert_symbol($2, $1, size($1) * atoi($4), yylineno, "global", "-");
    }
    | type IDENTIFIER '[' NUMBER ']' '[' NUMBER ']' SEMICOLON {
        insert_symbol($2, $1, size($1) * atoi($4) * atoi($7), yylineno, "global", "-");
    }
    ;

includes:
    includes INCLUDE HEADER_FILE
    | /* empty */
    ;

functions:
    functions function
    | function
    ;

function:
    type IDENTIFIER '(' parameter_list ')' '{' declarations '}'
    {
        insert_symbol($2, $1, 0, yylineno, "global", "-");
    }
    | type IDENTIFIER '(' parameter_list ')' '{' statements '}'
    ;

parameter_list:
    /* empty */                      // No parameters (e.g., `void func()`)
    | type IDENTIFIER                 // Single parameter (e.g., `int a`)
    | parameter_list ',' type IDENTIFIER  // Multiple parameters (e.g., `int a, float b`)
    ;

statements:
    statement
    | statements statement
    ;

statement:
    declaration
    | assignment
    | function_call
    | return_statement
    | ';'
    ;

assignment:
    IDENTIFIER ASSIGN NUMBER SEMICOLON   // `x = 10;`
    | IDENTIFIER ASSIGN FLOAT SEMICOLON  // `x = 5.5;`
    | IDENTIFIER ASSIGN IDENTIFIER SEMICOLON  // `x = y;`
    ;

function_call:
    IDENTIFIER '(' ')' SEMICOLON    // `func();`
    | IDENTIFIER '(' argument_list ')' SEMICOLON  // `func(a, b);`
    ;

argument_list:
    IDENTIFIER
    | argument_list ',' IDENTIFIER
    ;

return_statement:
    RETURN NUMBER SEMICOLON  // `return 10;`
    | RETURN IDENTIFIER SEMICOLON  // `return x;`
    ;



type:
    INT { $$ = strdup("int"); }
    | FLOAT { $$ = strdup("float"); }
    | CHAR { $$ = strdup("char"); }
    | DOUBLE { $$ = strdup("double"); }
    ;

%%

int main() {
    yyin = fopen("sample_input1.c", "r");
    if (!yyin) {
        printf("Error opening file.\n");
        return 1;
    }
    init_table();
    yyparse();
    fclose(yyin);
    return 0;
}

#ifndef SYM_TAB_H
#define SYM_TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a symbol (identifier)
typedef struct Symbol {
  char name[50];       // Identifier name
  char type[20];       // Data type (int, float, etc.)
  int size;            // Size of data type
  int line_no;         // Line number of declaration
  char scope[20];      // Scope (global, local, etc.)
  char value[50];      // Value (if assigned)
  struct Symbol *next; // Pointer to next symbol
} Symbol;

// Function prototypes
void init_table();
Symbol *init_symbol(char *name, char *type, int size, int line_no, char *scope,
                    char *value);
void insert_symbol(char *name, char *type, int size, int line_no, char *scope,
                   char *value);
void insert_val(char *name, char *value);
int check_sym_tab(char *name);
void display_sym_tab();
int size(char *type);

#endif

#include "sym_tab.h"

Symbol *head = NULL; // Head of the linked list

// Initialize the symbol table
void init_table() {
    head = NULL;
}

// Create a new symbol
Symbol* init_symbol(char* name, char* type, int size, int line_no, char* scope, char* value) {
    Symbol* new_symbol = (Symbol*)malloc(sizeof(Symbol));
    strcpy(new_symbol->name, name);
    strcpy(new_symbol->type, type);
    new_symbol->size = size;
    new_symbol->line_no = line_no;
    strcpy(new_symbol->scope, scope);
    strcpy(new_symbol->value, value);
    new_symbol->next = NULL;
    return new_symbol;
}

// Insert a new symbol
void insert_symbol(char* name, char* type, int size, int line_no, char* scope, char* value) {
    if (check_sym_tab(name)) {
        printf("Error: Identifier '%s' is already declared.\n", name);
        return;
    }
    Symbol* new_symbol = init_symbol(name, type, size, line_no, scope, value);
    new_symbol->next = head;
    head = new_symbol;
}

// Update the value of a symbol
void insert_val(char* name, char* value) {
    Symbol* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            strcpy(temp->value, value);
            return;
        }
        temp = temp->next;
    }
    printf("Error: Identifier '%s' not found.\n", name);
}

// Check if a symbol exists in the table
int check_sym_tab(char* name) {
    Symbol* temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return 1;
        temp = temp->next;
    }
    return 0;
}

// Display the symbol table
void display_sym_tab() {
    Symbol* temp = head;
    printf("\nSymbol Table:\n");
    printf("------------------------------------------------------\n");
    printf("| Name     | Type  | Size | Line | Scope  | Value    |\n");
    printf("------------------------------------------------------\n");
    while (temp) {
        printf("| %-8s | %-5s | %-4d | %-4d | %-6s | %-8s |\n",
               temp->name, temp->type, temp->size, temp->line_no, temp->scope, temp->value);
        temp = temp->next;
    }
    printf("------------------------------------------------------\n");
}

// Get the size of a data type
int size(char* type) {
    if (strcmp(type, "int") == 0) return 4;
    if (strcmp(type, "float") == 0) return 4;
    if (strcmp(type, "double") == 0) return 8;
    if (strcmp(type, "char") == 0) return 1;
    return 0;
}

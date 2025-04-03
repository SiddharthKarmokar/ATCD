#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int priority(char ch) {
    switch (ch) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '(': return 0;  // Lowest priority to keep '(' in stack
    }
    return -1;
}

void solve(int* stack, int* top, char op) {
    int b = stack[--(*top)];
    int a = stack[--(*top)];
    int res;

    switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero\n");
                exit(1);
            }
            res = a / b;
            break;
    }
    
    stack[(*top)++] = res;
}

int main() {
    FILE *file = fopen("in.txt", "r");
    if (!file) {
        printf("Error: File not found\n");
        return 1;
    }
    
    char string[100], temp[100];
    fgets(string, sizeof(string), file);
    fclose(file);

    int index = 0, stack[100], top = 0;
    char st[100];  // Operator stack
    int t = 0;     // Operator stack index

    for (int i = 0; i < strlen(string); i++) {
        if (isspace(string[i])) continue;

        if (isdigit(string[i])) {
            temp[index++] = string[i];
        } else {
            if (index > 0) {  
                temp[index] = '\0';
                stack[top++] = atoi(temp);
                index = 0;
            }

            if (string[i] == '(') {
                st[t++] = string[i];
            } else if (string[i] == ')') {
                while (t > 0 && st[t - 1] != '(') {
                    solve(stack, &top, st[--t]);
                }
                t--;  // Remove '('
            } else {
                while (t > 0 && priority(st[t - 1]) >= priority(string[i])) {
                    solve(stack, &top, st[--t]);
                }
                st[t++] = string[i];
            }
        }
    }

    if (index > 0) {
        temp[index] = '\0';
        stack[top++] = atoi(temp);
    }

    while (t > 0) {
        solve(stack, &top, st[--t]);
    }

    printf("answer: %d\n", stack[0]);
    return 0;
}

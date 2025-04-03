#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int tempCount = 1;
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop();
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }
    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void generateTAC(char *postfix) {
    char operands[MAX][10];
    int operandTop = -1;
    char buffer[10];

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            snprintf(operands[++operandTop], 10, "%c", postfix[i]);
        } else {
            char op2[10], op1[10];
            strcpy(op2, operands[operandTop--]);
            strcpy(op1, operands[operandTop--]);
            snprintf(buffer, 10, "t%d", tempCount);
            printf("%s = %s %c %s\n", buffer, op1, postfix[i], op2);
            strcpy(operands[++operandTop], buffer);
            tempCount++;
        }
    }
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter an arithmetic expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("\nThree-Address Code:\n");
    generateTAC(postfix);
    
    return 0;
}

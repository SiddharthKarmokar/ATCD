#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char left;
    char right[50];
} Prod;

int main() {
    Prod prods[100];  // Increase size to allow multiple alternatives
    int prodCount = 0;
    int n;
    
    printf("Enter number of productions (lines): ");
    scanf("%d", &n);
    getchar(); // consume newline after number input
    
    // Read each production line
    // Each line can contain alternatives separated by '|'
    for (int i = 0; i < n; i++) {
        char line[100];
        fgets(line, sizeof(line), stdin);
        
        // Remove trailing newline, if present.
        line[strcspn(line, "\n")] = '\0';
        
        // Expect line in the format: X->Y1|Y2|...|Yk
        // The left-hand side is the first character.
        char left = line[0];
        
        // Find the "->" substring.
        char *arrowPos = strstr(line, "->");
        if (arrowPos == NULL) {
            printf("Invalid production format.\n");
            continue;
        }
        
        // The alternatives start after "->"
        char *rhs = arrowPos + 2;
        
        // Use strtok to split alternatives by '|'
        char *token = strtok(rhs, "|");
        while (token != NULL) {
            // Copy the alternative into a new production
            prods[prodCount].left = left;
            strcpy(prods[prodCount].right, token);
            prodCount++;
            token = strtok(NULL, "|");
        }
    }
    
    // Now prodCount is the total number of productions
    // For epsilon, we assume "e" represents epsilon.
    
    // Compute Nullable Nonterminals
    bool null[26] = { false };
    bool change;
    do {
        change = false;
        for (int i = 0; i < prodCount; i++) {
            int l = prods[i].left - 'A';
            if (null[l])
                continue;
            
            if (strcmp(prods[i].right, "e") == 0) {
                null[l] = true;
                change = true;
                continue;
            }
            
            bool allnull = true;
            for (int j = 0; j < strlen(prods[i].right); j++) {
                char c = prods[i].right[j];
                if (c >= 'A' && c <= 'Z') {
                    if (!null[c - 'A']) {
                        allnull = false;
                        break;
                    }
                } else { // terminal encountered; not nullable
                    allnull = false;
                    break;
                }
            }
            if (allnull) {
                null[l] = true;
                change = true;
            }
        }
    } while (change);
    
    // Compute Trailing Sets
    bool trail[26][26] = { { false } };
    do {
        change = false;
        for (int i = 0; i < prodCount; i++) {
            int l = prods[i].left - 'A';
            if (strcmp(prods[i].right, "e") == 0)
                continue;
            
            // Process the right-hand side from right to left
            for (int j = strlen(prods[i].right) - 1; j >= 0; j--) {
                char c = prods[i].right[j];
                if (c >= 'a' && c <= 'z') {  // terminal encountered
                    if (!trail[l][c - 'a']) {
                        trail[l][c - 'a'] = true;
                        change = true;
                    }
                    break;
                }
                else if (c >= 'A' && c <= 'Z') { // nonterminal encountered
                    int idx = c - 'A';
                    // Merge trailing set of the encountered nonterminal into l's trailing set.
                    for (int k = 0; k < 26; k++) {
                        if (trail[idx][k] && !trail[l][k]) {
                            trail[l][k] = true;
                            change = true;
                        }
                    }
                    if (!null[idx]) {
                        break;
                    }
                }
            }
        }
    } while (change);
    
    // Print Trailing Sets for nonterminals that appear on the left side
    bool printed[26] = { false };
    for (int i = 0; i < prodCount; i++) {
        printed[prods[i].left - 'A'] = true;
    }
    for (int i = 0; i < 26; i++) {
        if (printed[i]) {
            printf("TRAILING(%c): { ", 'A' + i);
            for (int j = 0; j < 26; j++) {
                if (trail[i][j])
                    printf("%c ", 'a' + j);
            }
            printf("}\n");
        }
    }
    
    return 0;
}
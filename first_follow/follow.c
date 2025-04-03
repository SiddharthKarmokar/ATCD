#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char nonterminal[10];
char rhs[10][10][10];
char first[10][10];
char follow[10][10];

void findfirst(int num, int n) {
    if (first[num][0] != '\0') return;

    int first_it = 0;
    for (int idx = 0; rhs[num][idx][0] != '\0'; idx++) {
        char *prod = rhs[num][idx];

        if (!(prod[0] >= 'A' && prod[0] <= 'Z')) {
            if (!strchr(first[num], prod[0])) {
                first[num][first_it++] = prod[0];
            }
        } else {
            int req_idx = -1;
            for (int i = 0; i < n; i++) {
                if (nonterminal[i] == prod[0]) {
                    req_idx = i;
                    break;
                }
            }
            findfirst(req_idx, n);
            int ti = 0;
            while (first[req_idx][ti] != '\0') {
                if (!strchr(first[num], first[req_idx][ti])) {
                    first[num][first_it++] = first[req_idx][ti];
                }
                ti++;
            }
        }
    }
    return;
}

int isnonterminal(char symbol) {
    return (symbol >= 'A' && symbol <= 'Z');
}

void addfollow(int idx, char symbol) {
    if (strchr(follow[idx], symbol)) return;
    int len = strlen(follow[idx]);
    follow[idx][len] = symbol;
    follow[idx][len + 1] = '\0';
}

void findfollow(int n) {
    addfollow(0, '$'); 

    int change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < n; i++) {
            char lhs = nonterminal[i];

            for (int j = 0; rhs[i][j][0] != '\0'; j++) {
                char *prod = rhs[i][j];

                for (int k = 0; prod[k] != '\0'; k++) {
                    char curr = prod[k];

                    if (isnonterminal(curr)) {
                        int curridx = -1;
                        for (int m = 0; m < n; m++) {
                            if (nonterminal[m] == curr) {
                                curridx = m;
                                break;
                            }
                        }

                        if (prod[k + 1] != '\0') {
                            char next = prod[k + 1];

                            if (!isnonterminal(next)) {
                                if (!strchr(follow[curridx], next)) {
                                    addfollow(curridx, next);
                                    change = 1;
                                }
                            } else {
                                int nextidx = -1;
                                for (int m = 0; m < n; m++) {
                                    if (nonterminal[m] == next) {
                                        nextidx = m;
                                        break;
                                    }
                                }

                                // Add first(next) to follow(curr)
                                for (int m = 0; first[nextidx][m] != '\0'; m++) {
                                    if (first[nextidx][m] != 'e' && !strchr(follow[curridx], first[nextidx][m])) {
                                        addfollow(curridx, first[nextidx][m]);
                                        change = 1;
                                    }
                                }

                                // If first(next) contains epsilon, propagate follow(i) to follow(curr)
                                if (strchr(first[nextidx], 'e')) {
                                    for (int m = 0; follow[i][m] != '\0'; m++) {
                                        if (!strchr(follow[curridx], follow[i][m])) {
                                            addfollow(curridx, follow[i][m]);
                                            change = 1;
                                        }
                                    }
                                }
                            }
                        } else {
                            // If it's the last symbol in the production
                            for (int m = 0; follow[i][m] != '\0'; m++) {
                                if (!strchr(follow[curridx], follow[i][m])) {
                                    addfollow(curridx, follow[i][m]);
                                    change = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of productions: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        char input[20];
        scanf("%s", input);

        nonterminal[i] = input[0];

        int rhsidx = 0, symidx = 0;
        for (int j = 3; input[j] != '\0'; j++) {
            if (input[j] == '|') {
                rhs[i][rhsidx][symidx] = '\0';
                rhsidx++;
                symidx = 0;
            } else {
                rhs[i][rhsidx][symidx++] = input[j];
            }
        }
        rhs[i][rhsidx][symidx] = '\0';
    }

    // Calculate FIRST sets
    for (int i = 0; i < n; i++) {
        findfirst(i, n);
    }

    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = {", nonterminal[i]);
        for (int j = 0; first[i][j] != '\0'; j++) {
            printf("%c ", first[i][j]);
        }
        printf("}\n");
    }

    // Calculate FOLLOW sets
    findfollow(n);

    for (int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = {", nonterminal[i]);
        for (int j = 0; follow[i][j] != '\0'; j++) {
            printf("%c ", follow[i][j]);
        }
        printf("}\n");
    }

    return 0;
}
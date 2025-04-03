#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define MAX_DFA_STATES 100

int nfa[MAX_STATES][MAX_SYMBOLS][MAX_STATES]; // NFA transition table
int dfa[MAX_DFA_STATES][MAX_SYMBOLS]; // DFA transition table
int dfa_states[MAX_DFA_STATES][MAX_STATES]; // Stores DFA state as a subset of NFA states
int dfa_count = 0;
int num_states, num_symbols;

// Checks if a subset already exists in DFA states
int find_subset(int subset[MAX_STATES]) {
    for (int i = 0; i < dfa_count; i++) {
        if (memcmp(dfa_states[i], subset, sizeof(int) * num_states) == 0) {
            return i;
        }
    }
    return -1;
}

// Computes the epsilon closure of a set (Not needed for no-epsilon case)
void compute_dfa() {
    int queue[MAX_DFA_STATES][MAX_STATES];
    int front = 0, rear = 0;

    memset(dfa, -1, sizeof(dfa));
    memset(dfa_states, 0, sizeof(dfa_states));

    dfa_states[0][0] = 1; // Start state of DFA is {0} (Assuming NFA starts at state 0)
    dfa_count++;

    memcpy(queue[rear++], dfa_states[0], sizeof(int) * num_states);

    while (front < rear) {
        int current_state[MAX_STATES];
        memcpy(current_state, queue[front++], sizeof(int) * num_states);

        int dfa_index = find_subset(current_state);

        for (int symbol = 0; symbol < num_symbols; symbol++) {
            int new_subset[MAX_STATES] = {0};
            for (int i = 0; i < num_states; i++) {
                if (current_state[i]) {
                    for (int j = 0; j < num_states; j++) {
                        if (nfa[i][symbol][j]) {
                            new_subset[j] = 1;
                        }
                    }
                }
            }
            
            int subset_index = find_subset(new_subset);
            if (subset_index == -1) {
                subset_index = dfa_count++;
                memcpy(dfa_states[subset_index], new_subset, sizeof(int) * num_states);
                memcpy(queue[rear++], new_subset, sizeof(int) * num_states);
            }
            dfa[dfa_index][symbol] = subset_index;
        }
    }
}

void print_dfa() {
    printf("\nDFA Transition Table:\n");
    printf("State ");
    for (int i = 0; i < num_symbols; i++) printf("%d ", i);
    printf("\n");
    
    for (int i = 0; i < dfa_count; i++) {
        printf(" %d    ", i);
        for (int j = 0; j < num_symbols; j++) {
            if (dfa[i][j] == -1) printf("- ");
            else printf("%d ", dfa[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("Enter number of NFA states: ");
    scanf("%d", &num_states);
    printf("Enter number of input symbols: ");
    scanf("%d", &num_symbols);

    printf("Enter NFA transition table (-1 for no transition):\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            printf("State %d, Symbol %d: ", i, j);
            int count, state;
            scanf("%d", &count);
            for (int k = 0; k < count; k++) {
                scanf("%d", &state);
                nfa[i][j][state] = 1;
            }
        }
    }
    
    compute_dfa();
    print_dfa();
    return 0;
}

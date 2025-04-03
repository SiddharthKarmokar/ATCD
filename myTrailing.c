#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct {
  char left;
  char right[50];
} prod;

bool is_terminal(char c) { return !(c >= 'A' && c <= 'Z'); }

int main() {
  prod p[50];
  int count = 0;
  int n;
  printf("Enter the number of productions: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    char input[500];
    scanf("%s", input);
    char left = input[0];
    char *arrowpos = strstr(input, "->");
    char *rhs = arrowpos + 2;
    char temp[50];
    int pos = 0;

    int len = strlen(rhs);
    for (int j = 0; j <= len; j++) {
      if (rhs[j] == '|' || rhs[j] == '\0') {
        temp[pos] = '\0';
        p[count].left = left;
        strcpy(p[count].right, temp);
        pos = 0;
        count++;
      } else {
        temp[pos++] = rhs[j];
      }
    }
  }

  bool change;
  bool null[26] = {false};
  do {
    change = false;
    for (int i = 0; i < count; i++) {
      int l = p[i].left - 'A';
      if (null[l])
        continue;
      if (strcmp(p[i].right, "e") == 0) {
        null[l] = true;
        change = true;
        continue;
      }

      bool isallnull = true;
      for (int j = 0; j < strlen(p[i].right); j++) {
        char c = p[i].right[j];
        if (c >= 'A' && c <= 'Z') {
          if (!null[c - 'A']) {
            isallnull = false;
            break;
          }
        } else {
          isallnull = false;
          break;
        }
      }
      if (isallnull) {
        null[l] = true;
        change = true;
      }
    }
  } while (change);

  // Use character arrays instead of the 2D boolean array
  char trail[26][50] = {{0}};

  do {
    change = false;
    for (int i = 0; i < count; i++) {
      int l = p[i].left - 'A';
      if (strcmp(p[i].right, "e") == 0) {
        continue;
      }

      for (int j = strlen(p[i].right) - 1; j >= 0; j--) {
        char c = p[i].right[j];
        if (is_terminal(c)) {
          // Check if c is already in trail[l]
          bool found = false;
          for (int k = 0; k < strlen(trail[l]); k++) {
            if (trail[l][k] == c) {
              found = true;
              break;
            }
          }

          if (!found) {
            int len = strlen(trail[l]);
            trail[l][len] = c;
            trail[l][len + 1] = '\0';
            change = true;
          }
          break;
        } else if (c >= 'A' && c <= 'Z') {
          int idx = c - 'A';
          // Add all characters from trail[idx] to trail[l]
          for (int k = 0; k < strlen(trail[idx]); k++) {
            char t = trail[idx][k];
            bool found = false;
            for (int m = 0; m < strlen(trail[l]); m++) {
              if (trail[l][m] == t) {
                found = true;
                break;
              }
            }

            if (!found) {
              int len = strlen(trail[l]);
              trail[l][len] = t;
              trail[l][len + 1] = '\0';
              change = true;
            }
          }
          if (!null[idx])
            break;
        }
      }
    }
  } while (change);

  bool printed[26] = {false};
  for (int i = 0; i < count; i++) {
    printed[p[i].left - 'A'] = true;
  }

  for (int i = 0; i < 26; i++) {
    if (printed[i]) {
      printf("TRAILING(%c): { ", 'A' + i);
      for (int j = 0; j < strlen(trail[i]); j++) {
        printf("%c ", trail[i][j]);
      }
      printf("}\n");
    }
  }
  return 0;
}
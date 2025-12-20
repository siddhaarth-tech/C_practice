/*
Exercise 1-24:
Write a program to check a C program for rudimentary syntax errors like
unmatched parentheses, brackets and braces. Don't forget about quotes.
*/

#include <stdio.h>

int main() {
    int inQuote = 0;
    /* Outside quotes */
    int p = 0, b = 0, c = 0;
    /* Inside quotes */
    int qp = 0, qb = 0, qc = 0;
    char ch;
    while ((ch = getchar()) != EOF) {
        if (ch == '"') {
            inQuote = !inQuote;
            continue;
        }
        /* Outside quotes */
        if (!inQuote) {
            if (ch == '(') p++;
            else if (ch == ')') p--;
            else if (ch == '[') b++;
            else if (ch == ']') b--;
            else if (ch == '{') c++;
            else if (ch == '}') c--;
            if (p < 0 || b < 0 || c < 0) {
                printf("SYNTAX ERROR: Unmatched bracket outside quotes\n");
                return 0;
            }
        }
        /* Inside quotes */
        else {
            if (ch == '(') qp++;
            else if (ch == ')') qp--;
            else if (ch == '[') qb++;
            else if (ch == ']') qb--;
            else if (ch == '{') qc++;
            else if (ch == '}') qc--;
            if (qp < 0 || qb < 0 || qc < 0) {
                printf("SYNTAX ERROR: Unmatched bracket inside quotes\n");
                return 0;
            }
        }
    }
    if (inQuote)
        printf("SYNTAX ERROR: Unclosed double quote\n");
    else if (p || b || c)
        printf("SYNTAX ERROR: Unmatched bracket outside quotes\n");
    else if (qp || qb || qc)
        printf("SYNTAX ERROR: Unmatched bracket inside quotes\n");
    else
        printf("NO SYNTAX ERRORS\n");

    return 0;
}

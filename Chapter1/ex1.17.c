/*Write a program to print all input lines that are longer than 80 characters.*/

#include <stdio.h>
#define MAXLINE 1000

int getline_custom(char line[], int maxline);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        if (len > 80)
            printf("%s", line);
    }

    return 0;
}

int getline_custom(char s[], int lim) {
    int c, i = 0, len = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        len++;
        if (i < lim - 1) {
            s[i++] = c; 
        }
    }

    if (c == '\n') {
        len++;
        if (i < lim - 1)
            s[i++] = c;
    }

    s[i] = '\0';
    return len; 
}

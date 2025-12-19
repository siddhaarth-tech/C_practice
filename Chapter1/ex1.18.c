/*Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines.*/
#include <stdio.h>
#define MAXLINE 1000

int getline_custom(char line[], int maxline);

int main() {
    int len, i;
    char line[MAXLINE];

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        for (i = len - 1; i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'); --i)
            ;
        line[i + 1] = '\n';
        line[i + 2] = '\0';
        
        if (i >= 0) 
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

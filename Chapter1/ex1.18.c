/*Write a program to remove trailing blanks and tabs from each line of input,
and to delete entirely blank lines.*/
#include <stdio.h>
#define MAXLINE 1000

int getline_custom(char line[], int maxline);

int getline_custom(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}
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


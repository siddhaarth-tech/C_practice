/*Write a program to print all input lines that are longer than 80 characters.
Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of inpu*/
#include <stdio.h>
#define MAXLINE 1000


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
    int len;
    char line[MAXLINE];

    while ((len = getline_custom(line, MAXLINE)) > 0) {
        if (len > 80)
            printf("%s", line);
    }

    return 0;
}


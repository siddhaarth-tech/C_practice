/*Write a program to print all input lines that are longer than 80 characters.
Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of inpu*/
#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 80)
            printf("%s", line);
    }

    return 0;
}


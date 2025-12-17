/*Write a program to count blanks, tabs, and newlines.*/
#include <stdio.h>

int main() {
    int ch, blanks = 0, tabs = 0, lines = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ') blanks++;
        else if (ch == '\t') tabs++;
        else if (ch == '\n') lines++;
    }
    printf("%d %d %d\n", blanks, tabs, lines);
    return 0;
}

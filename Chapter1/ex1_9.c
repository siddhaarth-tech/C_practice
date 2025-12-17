/*Write a program to copy its input to its output, replacing each string of one or
more blanks by a single blank.*/
#include <stdio.h>

int main() {
    int ch, last = 0;
    while ((ch = getchar()) != EOF) {
        if (ch != ' ' || last != ' ')
            putchar(ch);
        last = ch;
    }
    return 0;
}

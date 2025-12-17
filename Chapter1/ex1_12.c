/*Write a program that prints its input one word per line.*/
#include <stdio.h>

int main() {
    int ch, inWord = 0;
    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (inWord) {
                putchar('\n');
                inWord = 0;
            }
        } else {
            putchar(ch);
            inWord = 1;
        }
    }
    return 0;
}

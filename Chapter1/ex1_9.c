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

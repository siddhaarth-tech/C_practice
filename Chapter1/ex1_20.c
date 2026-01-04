#include <stdio.h>

#define TABSTOP 5

int main(void)
{
    int c;
    int col = 0;  
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            int spaces = TABSTOP - (col % TABSTOP);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
                col++;
            }
        }
        else if (c == '\n') {
            putchar(c);
            col = 0;   
        }
        else {
            putchar(c);
            col++;
        }
    }

    return 0;
}

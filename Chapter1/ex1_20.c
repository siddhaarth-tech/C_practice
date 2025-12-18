/* 
Exercise 1-20:
Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume tab stops every 8 columns.
*/
#include <stdio.h>

#define TABSTOP 8

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


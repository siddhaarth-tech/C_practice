/*
Exercise 1-22:
Write a program to fold long input lines into two or more shorter lines
after the last non-blank character before column 40.
*/
#include <stdio.h>

#define MAXCOL 40

int main(void)
{
    int c;
    int col = 0;
    int last_blank = -1;
    char line[MAXCOL + 1];

    while ((c = getchar()) != EOF) {

        line[col] = c;

        if (c == ' ' || c == '\t')
            last_blank = col;

        col++;

        if (c == '\n') {
            for (int i = 0; i < col; i++)
                putchar(line[i]);
            col = 0;
            last_blank = -1;
        }
        else if (col >= MAXCOL) {
            if (last_blank >= 0) {
                for (int i = 0; i <= last_blank; i++)
                    putchar(line[i]);
                putchar('\n');

                col = col - last_blank - 1;
                for (int i = 0; i < col; i++)
                    line[i] = line[last_blank + 1 + i];
            } else {
                for (int i = 0; i < col; i++)
                    putchar(line[i]);
                putchar('\n');
                col = 0;
            }
            last_blank = -1;
        }
    }

    return 0;
}


/*
Exercise 1-22:
Write a program to fold long input lines into two or more shorter lines
after the last non-blank character before column 40.
*/

#include <stdio.h>
#define MAX 40
int main()
{
    int c;
    int col = 0;
    int last_space = -1;
    char line[1000];
    int i = 0;
    while ((c = getchar()) != EOF)
    {
        line[i++] = c;
        col++;
        if (c == ' ' || c == '\t')
            last_space = i - 1;

        if (c == '\n')
        {
            for (int j = 0; j < i; j++)
                putchar(line[j]);

            i = 0;
            col = 0;
            last_space = -1;
        }
        else if (col >= MAX)
        {
            if (last_space != -1)
            {
                for (int j = 0; j <= last_space; j++)
                    putchar(line[j]);
                putchar('\n');
                i = i - last_space - 1;
                for (int j = 0; j < i; j++)
                    line[j] = line[last_space + 1 + j];
            }
            else
            {
                for (int j = 0; j < i; j++)
                    putchar(line[j]);
                putchar('\n');
                i = 0;
            }
            col = i;
            last_space = -1;
        }
    }
    return 0;
}

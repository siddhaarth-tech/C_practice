/* 
Exercise 1-20:
Write a program detab that replaces tabs in the input with the proper number
of blanks to space to the next tab stop. Assume tab stops every 8 columns.
*/

#include <stdio.h>
#define TAB 8
int main()
{
    int c;
    int col = 0; // current column position
    int space;   // number of spaces needed
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            space = TAB - (col % TAB);
            while (space > 0)
            {
                putchar(' ');
                col++;
                space--;
            }
        }
        else
        {
            putchar(c);
            col++;
            if (c == '\n')
                col = 0;
        }
    }
    return 0;
}

/*
Exercise 1-21:
Write a program entab that replaces strings of blanks with the minimum
number of tabs and blanks to achieve the same spacing.
*/

#include <stdio.h>
#define TAB 8
int main()
{
    int c;
    int col = 0;   // column counter
    int blanks = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            blanks++;
            col++;
            if (col % TAB == 0)
            {
                putchar('\t');
                blanks = 0;
            }
        }
        else
        {
            while (blanks > 0)
            {
                putchar(' ');
                blanks--;
            }
            putchar(c);
            if (c == '\n')
                col = 0;
            else
                col++;
        }
    }
    return 0;
}

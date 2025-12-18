/*
Exercise 1-24:
Write a program to check a C program for unmatched (), {}, and [].
Ignore strings and character constants.
*/

#include <stdio.h>
int main()
{
    int c;
    int paren = 0;
    int brace = 0;
    int bracket = 0;
    int in_string = 0;
    int in_char = 0;
    while ((c = getchar()) != EOF)
    {
        if (in_string)
        {
            if (c == '"')
                in_string = 0;
        }
        else if (in_char)
        {
            if (c == '\'')
                in_char = 0;
        }
        else
        {
            if (c == '"')
                in_string = 1;
            else if (c == '\'')
                in_char = 1;
            else if (c == '(')
                paren++;
            else if (c == ')')
                paren--;
            else if (c == '{')
                brace++;
            else if (c == '}')
                brace--;
            else if (c == '[')
                bracket++;
            else if (c == ']')
                bracket--;
        }
    }
    if (paren != 0)
        printf("Unmatched parentheses\n");
    if (brace != 0)
        printf("Unmatched braces\n");
    if (bracket != 0)
        printf("Unmatched brackets\n");
    if (paren == 0 && brace == 0 && bracket == 0)
        printf("No syntax errors\n");
    return 0;
}

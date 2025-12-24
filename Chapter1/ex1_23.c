/*
Exercise 1-23:
Write a program to remove all comments from a C program.
Handle strings and character constants properly.
*/
#include <stdio.h>

int main(void)
{
    int c, prev = 0;
    int in_block_comment = 0;
    int in_string = 0;
    int in_char = 0;

    while ((c = getchar()) != EOF)
    {
        if (in_block_comment)
        {

            if (prev == '*' && c == '/'){
                in_block_comment = 0;
				prev=0;
				continue;}
        }
        else if (in_string)
        {
            putchar(c);
            if (c == '"' && prev != '\\')
                in_string = 0;
        }
        else if (in_char)
        {
            putchar(c);
            if (c == '\'' && prev != '\\')
                in_char = 0;
        }
        else
        {
            if (prev == '/' && c == '*')
            {
                in_block_comment = 1;
                prev = 0;
                continue;
            }
            else if (prev == '/' && c == '/')
            {
                while ((c = getchar()) != EOF && c != '\n')
                    ;
                putchar('\n');
                prev = 0;
                continue;
            }
            else
            {
                if (prev == '/' && c != '/' && c != '*')
                    putchar('/');

                if (c == '"')
                {
                    in_string = 1;
                    putchar(c);
                }
                else if (c == '\'')
                {
                    in_char = 1;
                    putchar(c);
                }
                else if (c != '/')
                {
                    putchar(c);
                }
            }
        }

        prev = c;
    }

    return 0;
}

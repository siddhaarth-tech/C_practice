/*
Exercise 2-2:

for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;

Write a loop equivalent to the for loop
without using && or ||.
*/

#include <stdio.h>
#define MAX 100

int main()
{
    int i = 0;
    int c;
    char s[MAX];
    while (1)
    {
        if (i >= MAX - 1)
            break;
        c = getchar();
        if (c == EOF)
            break;
        if (c == '\n')
            break;
        s[i] = c;
        i++;
    }

    printf("%d\n", i);

    return 0;
}

/*Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).*/
//atoi
#include <stdio.h>

int my_atoi(char *s);

int main(void)
{
    char s[100];

    printf("enter the number (string): ");
     scanf("%s",s);

    /* remove newline */
    char *p = s;
    while (*p != '\0') {
        if (*p == '\n') {
            *p = '\0';
            break;
        }
        p++;
    }

    int result = my_atoi(s);
    printf("after converted to int: %d\n", result);

    return 0;
}

int my_atoi(char *s)
{
    int n = 0;
    int sign = 1;

    /* skip whitespace */
    while (*s == ' ' || *s == '\t')
        s++;

    /* handle sign */
    if (*s == '+' || *s == '-') {
        sign = (*s == '-') ? -1 : 1;
        s++;
    }

    /* convert digits */
    while (*s >= '0' && *s <= '9') {
        n = n * 10 + (*s - '0');
        s++;
    }

    return sign * n;
}

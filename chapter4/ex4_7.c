/*Exercise 4-7Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?*/
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);
void ungets(const char s[]);

int main(void)
{
    char s[BUFSIZE];
    int c;

    printf("Enter a string: ");
    scanf("%s", s);

    ungets(s);   // push back entire string

    printf("added to buffer:\n");
    while ((c = getch()) != EOF) {
        putchar(c);
        if (c == '\n')
            break;
    }

    return 0;
}

void ungets(const char s[])
{
    int i = strlen(s);

    while (i > 0)
        ungetch(s[--i]);
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: buffer overflow\n");
    else
        buf[bufp++] = c;
}

int getch(void)
{
    if (bufp > 0)
        return buf[--bufp];
    else
        return getchar();
}

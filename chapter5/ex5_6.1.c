/*Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).*/

//getline
#include <stdio.h>

#define MAX 100

int my_getline(char *s, int max);

int main(void)
{
    char s[MAX];

    if (my_getline(s, MAX) > 0)
        printf("after getting input from my_getline function: %s\n", s);
    else
        printf("invalid\n");

    return 0;
}

int my_getline(char *s, int max)
{
    char *start = s;   // save starting address
    int c;

    // read characters using pointer
    while (max > 1 && (c = getchar()) != EOF && c != '\n') {
        *s = c;
        s++;
        max--;
    }

    // include newline if present
    if (c == '\n') {
        *s = '\n';
        s++;
    }

    *s = '\0';         // terminate string
    return s - start;  // return length
}

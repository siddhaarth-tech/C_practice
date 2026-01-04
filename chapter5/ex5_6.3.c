/*Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).*/
//reverse
#include <stdio.h>

void reverse(char *s);

int main(void)
{
    char s[100];

    printf("enter the string: ");
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

    reverse(s);

    printf("the string after reversed: %s\n", s);
    return 0;
}

void reverse(char *s)
{
    char *end = s;

    /* move end to last character */
    while (*end != '\0')
        end++;
    end--;

    /* swap characters from both ends */
    while (s < end) {
        char temp = *s;
        *s = *end;
        *end = temp;

        s++;
        end--;
    }
}

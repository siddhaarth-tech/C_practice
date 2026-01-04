//Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.

#include <stdio.h>

void my_strcat(char *s, char *t);

int main(void)
{
    char s[100];
    char t[100];

    printf("Enter the string s: ");
    scanf("%s", s);

    printf("Enter the string t: ");
    scanf("%s", t);
    my_strcat(s, t);
    
    printf("After concatenation: %s\n", s);

    return 0;
}

void my_strcat(char *s, char *t)
{
    /* move s to the end of the string */
    while (*s != '\0')
        s++;

    /* copy t to the end of s */
    while ((*s = *t) != '\0') {
        s++;
        t++;
    }
}

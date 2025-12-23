/*Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none.*/
#include <stdio.h>

int strindex(char s[], char t[])
{
    int i = 0, j, k, pos = -1;

    while (s[i] != '\0') {
        j = i;
        k = 0;

        while (t[k] != '\0' && s[j] == t[k]) {
            j++;
            k++;
        }

        if (t[k] == '\0')
            pos = i;

        i++;
    }
    return pos;
}

int main()
{
    char s[100], t[100];
    int index;

    printf("Enter main string: ");
    scanf("%99s", s);    
    printf("Enter substring: ");
    scanf("%99s", t);

    index = strindex(s, t);

    if (index != -1)
        printf("Rightmost occurrence at index %d\n", index);
    else
        printf("Substring not found\n");

    return 0;
}

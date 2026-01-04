/*
Exercise 2-4:
Write an alternative version of squeeze(s1, s2)
that deletes from s1 each character that matches
any character in s2.
*/
#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
    char s1[100];
    char s2[100];

    printf("Enter string s1: ");
    scanf("%[^\n]", s1);   // read full line with spaces

    printf("Enter string s2: ");
    scanf(" %s", s2);       // s2 usually has no spaces

    squeeze(s1, s2);

    printf("Result: %s\n", s1);

    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i, j, k;
    int found;

    for (i = k = 0; s1[i] != '\0'; i++)
    {
        found = 0;
        for (j = 0; s2[j] != '\0'; j++)
        {
            if (s1[i] == s2[j])
            {
                found = 1;
                break;
            }
        }

        if (!found)
            s1[k++] = s1[i];
    }

    s1[k] = '\0';
}

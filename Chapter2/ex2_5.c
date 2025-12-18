/*
Exercise 2-5:
Write the function any(s1,s2), which returns the first location in a string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.
*/

#include <stdio.h>
int any(char s1[], char s2[]);

int main()
{
    char s1[100];
    char s2[100];
    int pos;
    printf("Enter string s1: ");
    scanf(" %[^\n]", s1);
    printf("Enter string s2: ");
    scanf(" %s", s2);
    pos = any(s1, s2);
    if (pos == -1)
        printf("No character from s2 found in s1\n");
    else
        printf("First match at index:%d\n",pos);
    return 0;
}

int any(char s1[], char s2[])
{
    int i,j;
    for (i = 0; s1[i] != '\0'; i++)
    {
        for (j = 0; s2[j] != '\0'; j++)
        {
            if (s1[i] == s2[j])
                return i;   // first occurrence
        }
    }
    return -1;
}

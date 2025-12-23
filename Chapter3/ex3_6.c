/*Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough.*/

#include <stdio.h>
#include <string.h>

/* reverse string */
void reverse(char s[])
{
    int i, j;
    char temp;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

/* itoa with minimum field width */
void itoa(int n, char s[], int width)
{
    int i = 0, sign;

    if ((sign = n) < 0)
        n = -n;

    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        s[i++] = '-';

    while (i < width)
        s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

int main()
{
    int num, width;
    char str[50];

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Enter minimum field width: ");
    scanf("%d", &width);

    itoa(num, str, width);

    printf("Result: '%s'\n", str);

    return 0;
}

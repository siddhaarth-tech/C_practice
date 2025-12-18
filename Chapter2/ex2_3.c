/*
Exercise 2-3:
Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F.
*/

#include <stdio.h>

int htoi(char s[]);

int main()
{
    char hex[100];
    printf("Enter a hexadecimal number: ");
    scanf("%s", hex);
    printf("Decimal value: %d\n", htoi(hex));
    return 0;
}

int htoi(char s[])
{
    int i = 0;
    int value = 0;
    int digit;

    /* 0x or 0X */
    if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X'))
        i += 2;

    while (s[i] != '\0')
    {
        if (s[i] >= '0' && s[i] <= '9')
            digit = s[i] - '0';
        else if (s[i] >= 'a' && s[i] <= 'f')
            digit = s[i] - 'a' + 10;
        else if (s[i] >= 'A' && s[i] <= 'F')
            digit = s[i] - 'A' + 10;
        else
            break;   // invalid character

        value = value * 16 + digit;
        i++;
    }

    return value;
}

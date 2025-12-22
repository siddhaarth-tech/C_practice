/*Exercise 3-4. In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2wordsize-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs.*/

#include <stdio.h>
#include <limits.h>

/* itoa: convert int n to characters in s */
void itoa(int n, char s[])
{
    int i = 0;
    int sign = n;

    do {
        int digit = n % 10;
        if (digit < 0)
            digit = -digit;
        s[i++] = digit + '0';
    } while ((n /= 10) != 0);

    if (sign < 0)
        s[i++] = '-';

    s[i] = '\0';

    /* reverse string */
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = s[j];
        s[j] = s[k];
        s[k] = temp;
    }
}

int main(void)
{
    int n;
    char buf[50];

    printf("Enter an integer: ");
    scanf("%d", &n);

    itoa(n, buf);
    printf("String form: %s\n", buf);

    return 0;
}

/*Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.*/

#include <stdio.h>
#include <limits.h>

/* itob: convert integer n to base b character representation in s */
void itob(int n, char s[], int b)
{
    int i = 0;
    int sign = n;
    /* reject invalid bases */
    if (b < 2 || b > 36) {
        s[0] = '\0';
        return;
    }
    /* generate digits */
    do {
        int digit = n % b;
        if (digit < 0)
            digit = -digit;

        if (digit < 10)
            s[i++] = digit + '0';
        else
            s[i++] = digit - 10 + 'A';

    } while ((n /= b) != 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    /* reverse string */
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = s[j];
        s[j] = s[k];
        s[k] = tmp;
    }
}

int main(void)
{
    int n, b;
    char buf[50];
    printf("Enter an integer: ");
    scanf("%d", &n);
    printf("Enter base (2 to 36): ");
    scanf("%d", &b);
    itob(n, buf, b);
    if (buf[0] == '\0')
        printf("Invalid base!\n");
    else
        printf("Result: %s\n", buf);
    return 0;
}

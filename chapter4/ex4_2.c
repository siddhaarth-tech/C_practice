/*Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.

#include <ctype.h>
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) 
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    return sign * val / power;
}
*/

#include <stdio.h>
#include <ctype.h>

/* atof: convert string s to double; handle scientific notation */
double atof(char s[])
{
    double val, power;
    int i, sign, exp, exp_sign;

    /* skip white space */
    for (i = 0; isspace((unsigned char)s[i]); i++)
        ;

    /* sign */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    /* integer part */
    for (val = 0.0; isdigit((unsigned char)s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    /* fractional part */
    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit((unsigned char)s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    /* exponent part */
    if (s[i] == 'e' || s[i] == 'E') {
        i++;

        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;

        for (exp = 0; isdigit((unsigned char)s[i]); i++)
            exp = 10 * exp + (s[i] - '0');

        while (exp-- > 0)
            val = (exp_sign == 1) ? val * 10.0 : val / 10.0;
    }

    return val;
}

int main(void)
{
    char s[100];

    printf("Enter a number : ");
    scanf("%s", s);

    printf("Converted value: %f\n", atof(s));

    return 0;
}

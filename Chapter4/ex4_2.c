/*Exercise 4-2. Extend atof to handle scientific notation of the form
123.45e-6
where a floating-point number may be followed by e or E and an optionally signed exponent.*/


#include <stdio.h>
#include <ctype.h>

double atof_extended(const char s[])
{
    double val = 0.0, power = 1.0;
    int i = 0, sign = 1, exp_sign = 1, exp = 0;

    /* skip white space */
    while (isspace(s[i]))
        i++;

    /* sign */
    if (s[i] == '+' || s[i] == '-') {
        sign = (s[i] == '-') ? -1 : 1;
        i++;
    }

    /* integer part */
    while (isdigit(s[i])) {
        val = 10.0 * val + (s[i] - '0');
        i++;
    }

    /* fractional part */
    if (s[i] == '.') {
        i++;
        while (isdigit(s[i])) {
            val = 10.0 * val + (s[i] - '0');
            power *= 10.0;
            i++;
        }
    }

    val = sign * val / power;

    /* exponent part */
    if (s[i] == 'e' || s[i] == 'E') {
        i++;

        if (s[i] == '+' || s[i] == '-') {
            exp_sign = (s[i] == '-') ? -1 : 1;
            i++;
        }

        while (isdigit(s[i])) {
            exp = 10 * exp + (s[i] - '0');
            i++;
        }

        /* apply exponent */
        while (exp-- > 0)
            val = (exp_sign == 1) ? val * 10.0 : val / 10.0;
    }

    return val;
}

int main(void)
{
    char s[100];

    printf("Enter a number (can use scientific notation): ");
    scanf("%99s", s);

    printf("Converted value: %f\n", atof_extended(s));

    return 0;
}

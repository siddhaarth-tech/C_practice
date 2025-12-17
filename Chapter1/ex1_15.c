/*Rewrite the temperature conversion program of Section 1.2 to use a function
for conversion.*/
#include <stdio.h>

/* function declaration */
float fahr_to_celsius(float fahr);
int main()
{
    float fahr, celsius;
    float lower = 0;
    float upper = 300;
    float step = 20;
    fahr = lower;
    while (fahr <= upper)
    {
        celsius = fahr_to_celsius(fahr);
        printf("%6.1f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}
float fahr_to_celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}

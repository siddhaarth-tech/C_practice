/*Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

#include <stdio.h>
unsigned invert(unsigned x, int p, int n)
{
    /* invert n bits starting at position p */
    x = x ^ (((1U << n) - 1) << (p - n + 1));

    return x;
}
int main(void)
{
    unsigned x = 25;
    int p = 2;
    int n = 3;

    unsigned result = invert(x, p, n);

    printf("Result = %u\n", result);

    return 0;
}

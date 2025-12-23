/*Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.*/

#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
    /* invert n bits starting at position p and moving left */
    unsigned tempbits = ((1U << n) - 1) << p;
    return x ^ tempbits;
}

int main(void)
{
    unsigned x;
    int p, n;

    printf("Enter an unsigned integer (x): ");
    scanf("%u", &x);

    printf("Enter position p: ");
    scanf("%d", &p);

    printf("Enter number of bits n: ");
    scanf("%d", &n);

    unsigned result = invert(x, p, n);

    printf("Result = %u\n", result);

    return 0;
}

/*Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.*/

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned bitfield;

    /* n 1-bits */
    bitfield = (1U << n) - 1;

    /* clear n bits of x starting at position p */
    x &= ~(bitfield << p);

    /* insert rightmost n bits of y into x */
    x |= (y & bitfield) << p;

    return x;
}

int main(void)
{
    unsigned x, y;
    int p, n;

    printf("Enter value for x: ");
    scanf("%u", &x);

    printf("Enter value for y: ");
    scanf("%u", &y);

    printf("Enter position p: ");
    scanf("%d", &p);

    printf("Enter number of bits n: ");
    scanf("%d", &n);

    printf("Result: %u\n", setbits(x, p, n, y));

    return 0;
}

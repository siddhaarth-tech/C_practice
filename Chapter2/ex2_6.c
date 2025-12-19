/*Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.*/

#include <stdio.h>
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned ybits;
    /* extract rightmost n bits of y and shift to position */
    ybits = (y & ((1U << n) - 1)) << (p - n + 1);
    /* clear n bits in x starting at position p */
    x = x & ~(((1U << n) - 1) << (p - n + 1));
    /* insert the bits from y */
    x = x | ybits;
    return x;
}

int main(void)
{
    unsigned x = 45;   
    unsigned y = 6;    
    int p = 5;
    int n = 3;
    unsigned result = setbits(x, p, n, y);
    printf("%u\n", result);

    return 0;
}

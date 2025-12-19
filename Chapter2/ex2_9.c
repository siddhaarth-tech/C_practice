/*Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x. Explain why. Use this observation to write a faster version of bitcount.*/

#include <stdio.h>
int bitcount(unsigned x)
{
    int count = 0;

    while (x != 0) {
        x &= (x - 1);   // delete rightmost 1-bit
        count++;
    }

    return count;
}
int main(void)
{
    unsigned x = 45;   // 00101101

    printf("Number of setbits in %u is %d\n", x, bitcount(x));
    return 0;
}

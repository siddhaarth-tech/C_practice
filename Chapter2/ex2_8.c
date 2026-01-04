/*Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated
to the right by n positions.*/

#include <stdio.h>
unsigned rightrot(unsigned x, int n)
{
    int i;
    unsigned last_bit;

    for (i = 0; i < n; i++)
    {
        last_bit = x & 1;        // get right bit
        x = x >> 1;              // shift right
        x = x | (last_bit << 31); // put bit at left
    }

    return x;
}

int main(void)
{
    unsigned x ;   
    int n ;
    scanf("%u",&x);
    scanf("%d",&n);

    unsigned result = rightrot(x, n);

    printf("%u\n", result);

    return 0;
}

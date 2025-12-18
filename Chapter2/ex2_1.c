/*
Exercise:2.1
Write a program to determine the ranges of char, short, int, and long
variables, both signed and unsigned, by printing appropriate values from standard headers
and by direct computation. Harder if you compute them: determine the ranges of the various
floating-point types.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
    printf("signed char  : %d to %d\n",SCHAR_MIN,SCHAR_MAX);
    printf("unsigned char: 0 to %u\n\n",UCHAR_MAX);

    printf("signed short  : %d to %d\n",SHRT_MIN,SHRT_MAX);
    printf("unsigned short: 0 to %u\n\n",USHRT_MAX);

    printf("signed int   : %d to %d\n",INT_MIN,INT_MAX);
    printf("unsigned int : 0 to %u\n\n",UINT_MAX);

    printf("signed long   : %ld to %ld\n",LONG_MIN,LONG_MAX);
    printf("unsigned long : 0 to %lu\n\n",ULONG_MAX);

    printf("float    : %e to %e\n", FLT_MIN, FLT_MAX);
    printf("double  : %e to %e\n", DBL_MIN, DBL_MAX);
    printf("long double : %Le to %Le\n\n", LDBL_MIN, LDBL_MAX);
}
/*Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a
minimum, it should print non-graphic characters in octal or hexadecimal according to local
custom, and break long text lines.*/

#include<stdio.h>
#include<ctype.h>

#define MAXCOL 60

int main()
{
  int c;
  int col=0;
  while((c=getchar())!=EOF)
  {
    if(c=='\n')
    {
      putchar('\n');
      col=0;
    }
    else if(isprint(c))
    {
      putchar(c);
      col++;
    }
    else
    {
      printf("\\x%02x",(unsigned char)c);
      col=col+4;
    }
    
    if(col>=MAXCOL)
    {
      putchar('\n');
      col=0;
    }
  }
  return 0;
}

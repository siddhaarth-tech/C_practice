//Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design.

#include<stdio.h>
#define EMPTY (-2)

int buf=EMPTY;

void ungetch(int c);
int getch();

int main()
{
  ungetch('A');
  int c=getch();
  printf("%c\n",c);
  
  ungetch(EOF);
  c=getch();
  if(c==EOF)
  {
    printf("EOF received\n");
  }
  return 0;
}

void ungetch(int c)
{
  if(buf==EMPTY)
  {
    buf=c;
  }
  else
  { 
    printf("many character ");
  }
}

int getch()
{
  if(buf!=EMPTY)
  {
    int c=buf;
    buf=EMPTY;
    return c;
  }
  else
  {
    return getchar();
  }
}

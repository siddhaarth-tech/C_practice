/*Exercise 4-8Suppose that there will never be more than one character of pushback. Modify
getch and ungetch accordingly.*/
#include<stdio.h>

int buf=EOF;

int getch();
void ungetch();

int main()
{
  ungetch('A');
  int c=getch();
  printf("%c\n",c);
  return 0;
}

int getch()
{
  if(buf!=EOF)
  {
    int c=buf;
    buf=EOF;
    return c;
  }
  else
  {
    printf("there is no character");
  }
}

void ungetch(int c)
{
  if(buf==EOF)
  {
    buf=c;
  }
  else
  {
    printf("there are too many characters");
  }
}
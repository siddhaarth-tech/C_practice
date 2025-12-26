/*Exercise 4-7Write a routine ungets(s) that will push back an entire string onto the input.
Should ungets know about buf and bufp, or should it just use ungetch?*/
#include<stdio.h>
#include<string.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp=0;

int getch();
void ungetch(int c);
void ungets(const char s[]);

int main()
{
  int c;
  ungets("hello");
  
  while((c=getch())!=EOF)
  {
    putchar(c);
    if(c=='\n')
    {
      break;
    }
  }
  return 0;
}

void ungets(const char s[])
{
  int i=strlen(s);
  
  while(i>0)
  {
    ungetch(s[--i]);
  }
}

void ungetch(int c)
{
  if(bufp>=BUFSIZE)
  {
    printf("overflow");
  }
  else
  {
    buf[bufp++]=c;
  }
}

int getch()
{
  if(bufp>0)
  {
    return buf[--bufp];
  }
  else
  {
    return getchar();
  }
}
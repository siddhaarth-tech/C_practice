//Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.

#include<stdio.h>
#include<ctype.h>

#define BUFSIZE 100
#define SIZE 100

int buffer[BUFSIZE];
int bufp=0;

int getch();
void ungetch(int val);
int getint(int *p);

int main()
{
  int array[SIZE];
  int n=0;
  printf("enter the numbers : ");
  int status;
  while((status=getint(&array[n]))!=EOF)
  {  
    if(status>0)
    {
      n++;
    }
  }
  
  printf("the final array is : ");
  for(int i=0;i<n;i++)
  {
    printf("%d  ",array[i]);
  }
  printf("\n");
  return 0;
}

int getch()
{
  if(bufp>0)
  {
    bufp--;
    return buffer[bufp];
  }
  else
  {
    return getchar();
  }
}

void ungetch(int val)
{
  if(bufp<BUFSIZE)
  {
    buffer[bufp]=val;
    bufp++;
  }
  else
  {
    printf("overflow");
  }
}

int getint(int *p)
{
  int c;
  
  while(isspace(c=getch()))
  {
    ;
  }
  
  if(!isdigit(c) && c!='+' && c!='-' && c!=EOF)
  {
    ungetch(c);
    return 0;
  }
  
  int sign=(c=='-') ? -1 : 1;
  
  if(c=='+' || c=='-')
  {
    int next=getch();
    if(!isdigit(next))
    {
      ungetch(next);
      ungetch(c);
      return 0;
    }
    c=next;
  }
  
  *p=0;
  while(isdigit(c))
  {
    *p = (*p * 10) + (c-'0');
    c=getch();
  }
  *p = *p * sign;
  if(c!=EOF)
  {
    ungetch(c);
  }
  
  return c;
}
//Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?

#include<stdio.h>
#include<ctype.h>

#define BUFSIZE 100
#define SIZE 100

int buffer[BUFSIZE];
int bufp=0;

int getch();
void ungetch(int val);
int getfloat(float *p);

int main()
{
  float array[SIZE];
  int n=0;
  printf("enter the numbers : ");
  int status;
  while((status=getfloat(&array[n]))!=EOF)
  {  
    if(status>0)
    {
      n++;
    }
  }
  
  printf("the final array is : ");
  for(int i=0;i<n;i++)
  {
    printf("%.2f  ",array[i]);
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

int getfloat(float *p)
{
  int c;
  
  while(isspace(c=getch()))
  {
    ;
  }
  
  if(!isdigit(c) && c!='+' && c!='-' && c!=EOF && c!='.')
  {
    ungetch(c);
    return 0;
  }
  
  int sign=(c=='-') ? -1 : 1;
  
  if(c=='+' || c=='-')
  {
    int next=getch();
    if(!isdigit(next) && next!='.')
    {
      ungetch(next);
      ungetch(c);
      return 0;
    }
    c=next;
  }
  
  
  *p=0.0;
  while(isdigit(c))
  {
    *p = (*p * 10.0) + (c-'0');
    c=getch();
  }
  
  float power;
  if(c=='.')
  {
    power=1.0;
    while(isdigit(c=getch()))
    {
      *p = (*p * 10.0) + (c-'0');
      power=power * 10.0;
    }
    *p = *p / power ;
  }
  
  *p = *p * sign;
  if(c!=EOF)
  {
    ungetch(c);
  }
  
  return c;
}
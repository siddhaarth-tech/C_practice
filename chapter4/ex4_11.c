/*Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal
static variable.*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100
#define NUMBER '0'

int getop(char s[]);

int main()
{
  int type;
  char s[MAX];
  
  while((type=getop(s))!=EOF)
  {
    if(type==NUMBER)
    {
      printf("Number : %s\n",s);
    }
    else if(type!='\n')
    {
      printf("operator : %c\n",type);
    }
  }
  return 0;
}

int getop(char s[])
{
  int c;
  int i=0;
  
  static int lastc=0;
  
  if(lastc!=0)
  {
    c=lastc;
    lastc=0;
  }
  else
  {
    c=getchar();
  }
  
  while(c==' ' || c=='\t')
  {
    c=getchar();
  }
  
  if(c==EOF)
  {
    return EOF;
  }
  
  s[0]=c;
  s[1]='\0';
  
  if(!isdigit(c) && c!='.' && c!='-')
  {
    return c;
  }
  
  if(c=='-')
  {
    int next=getchar();
    if(!isdigit(next) && next!='.')
    {
      lastc=next;
      return '-';
    }
    s[++i]=next;
    c=next;
  }
  
  while(isdigit(c=getchar()))
  {
    s[++i]=c;
  }
  
  if(c=='.')
  {
    s[++i]=c;
    while(isdigit(c=getchar()))
    {
      s[++i]=c;
    }
  }
  
  s[++i]='\0';
  
  lastc=c;
  
  return NUMBER;
}

/*Exercise 4-10. An alternate organization uses getline to read an entire input line; this makes
getch and ungetch unnecessary. Revise the calculator to use this approach.*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXVAL 100
#define MAXLINE 100
#define NUMBER '0'

double val[MAXVAL];
int sp=0;

char line[MAXLINE];
int linepos=0;

void push(double val);
double pop();
int getop(char line[]);
int my_getline(char line[],int max);

int main()
{
  double op2;
  int type;
  char s[MAXLINE];
  
  while(my_getline(line,MAXLINE)>0)
  {
    linepos=0;
    while((type=getop(s))!='\0')
    {
      switch(type)
      {
        case NUMBER:
          push(atof(s));
          break;
        case '+':
          push(pop() + pop());
          break;
        case '*':
          push(pop() * pop());
          break;
        case '-':
          op2=pop();
          push(pop() - op2);
          break;
        case '/':
          op2=pop();
          if(op2!=0.0)
          { 
            push(pop() / op2);
          }
          else
          {
            printf("divide by zero error");
          }
          break;
        case '\n':
          if(sp>0)
          { 
            printf("%.8g\n",pop());
          }
          break;
        default:
          printf("Invalid");
          break;
      }
    }
  }
  return 0;
}

void push(double value)
{
  if(sp<MAXVAL)
  {
    val[sp]=value;
    sp++;
  }
  else
  {
    printf("overflow");
  }
}

double pop()
{
  if(sp>0)
  {
    sp--;
    return val[sp];
  }
  else
  {
    printf("underflow");
    return 0.0;
  }
}

int my_getline(char s[],int max)
{
  int i=0;
  int c;
  while((c=getchar())!=EOF && c!='\n' && i<max)
  {
    s[i]=c;
    i++;
  }
  
  if(c=='\n')
  {
    s[i]='\n';
    i++;
  }
  s[i]='\0';
  return i;
}

int getop(char s[])
{
  int i=0;
  int c;
  while((c=line[linepos])==' ' || c=='\t')
  {
    linepos++;
  }
 
  if(c=='\0')
  {
    return '\0';
  }
  
  if(c=='\n')
  {
    linepos++;
    return '\n';
  }
  s[0]=c;
  s[1]='\0';
  
  if(!isdigit(c) && c!='.' && c!='-')
  {
    linepos++;
    return c;
  }
  
  if(c=='-')
  {
    char next=line[linepos+1];
    if(!isdigit(next) && next!='.')
    {
      linepos++;
      return '-';
    }
    s[++i]=next;
    linepos+=2;
  }
  else
  {
    linepos++;
  }

  while(isdigit(line[linepos]))
  {
    s[++i]=line[linepos++];
  }
  
  if(line[linepos]=='.')
  {
    s[++i]=line[linepos++];
    while(isdigit(line[linepos]))
    {
      s[++i]=line[linepos++];
    }
  }
  
  s[++i]='\0';
  return NUMBER;
}
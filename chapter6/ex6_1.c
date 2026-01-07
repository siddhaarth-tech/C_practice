/*Exercise 6-1. Our version of getword does not properly handle underscores, string constants,
comments, or preprocessor control lines. Write a better version.*/


#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp=0;

int getword(char *word, int lim);
int getch(void);
void ungetch(int);

int main(void)
{
  char word[MAXWORD];

  while(getword(word,MAXWORD)!=EOF) 
  {
    if(isalpha(word[0])||word[0]=='_')
      printf("%s\n",word);
  }
  return 0;
}


int getword(char *word,int lim)
{
  int c,d;
  char *w =word;

  while (isspace(c = getch()))
  {
    ;
  }

  if(c==EOF)
    return EOF;

  if(c=='#') 
  {
    while ((c = getch()) != '\n' && c != EOF)
    {
      ;
    }
    return getword(word, lim);
  }

  if(c=='/') 
  {
    d=getch();
    if (d=='*') 
    {          
      while((c=getch())!=EOF)
        if (c=='*' && getch()=='/')
            break;
      return getword(word, lim);
    } 
    else if(d=='/') 
    { 
      while((c=getch())!='\n' && c!=EOF)
      {
        ;
      }
      return getword(word, lim);
    } 
    else 
    {
      ungetch(d);
    }
  }

  if(c=='"') 
  {
    while ((c = getch()) != '"' && c != EOF)
      if (c == '\\')
         getch();
    return getword(word, lim);
  }
  
  if(c=='\'') 
  {
    while ((c = getch()) != '\'' && c != EOF)
      if (c == '\\')
          getch();
    return getword(word, lim);
  }

  if(isalpha(c) || c=='_') 
  {
    *w++=c;
    while(--lim>0) 
    {
      c=getch();
      if(!isalnum(c) && c!='_') 
      {
        ungetch(c);
        break;
      }
      *w++ = c;
    }
    *w = '\0';
    return word[0];
  }

  *w='\0';
  return c;
}

int getch(void)
{
  return (bufp>0) ? buf[--bufp]:getchar();
}

void ungetch(int c)
{
  if(bufp<BUFSIZE)
    buf[bufp++]=c;
  else
    printf("ungetch: too many characters\n");
}

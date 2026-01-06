//Exercise 5-18. Make dcl recover from input errors.

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100

enum{NAME,PARENS,BRACKETS};

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int error=0;

int gettoken();
void dcl();
void dirdcl();
void skipline();

int main()
{
  while(gettoken()!=EOF)
  {
    error=0;
    
    strcpy(datatype,token);
    out[0]='\0';
    name[0]='\0';
    
    dcl();
    
    if(error)
    {
      skipline();
      printf("skipping  invalid declaration\n");
    }
    else if(tokentype!='\n')
    {
      printf("syntax error\n");
      skipline();
    }
    else
    {
      printf("%s:%s %s\n",name,out,datatype);
    }
  }
  return 0;
}

void dcl()
{
  int ns=0;
  
  while(gettoken()=='*')
  {
    ns++;
  }
  
  dirdcl();
  
  while(ns-- >0)
  {
    strcat(out," pointer to");
  }
}

void dirdcl()
{
  int type;
  
  if(tokentype=='(')
  {
    dcl();
    if(tokentype!=')')
    {
      printf("missing\n");
      error=1;
    }
  }
  else if(tokentype==NAME)
  {
    strcpy(name,token);
  }
  else
  {
    printf("error\n");
    error=1;
    return ;
  }
  
  while(!error && ((type=gettoken())==PARENS || type==BRACKETS))
  {
    if(type==PARENS)
    {
      strcat(out," function returning");
    }
    else
    {
      strcat(out," array");
      strcat(out,token);
      strcat(out," of");
    }
  }
}

int gettoken()
{
  int c;
  char *p=token;
  
  while((c=getchar())==' '|| c=='\t')
  {
    ;
  }
  
  if(c=='(')
  {
    if((c=getchar())==')')
    {
      strcpy(token,"()");
      return tokentype=PARENS;
    }
    else
    {
      ungetc(c,stdin);
      return tokentype='(';
    }
  }
  else if(c=='[')
  {
    *p++=c;
    while((*p++=getchar())!=']')
    {
      ;
    }
    
    *p='\0';
    return tokentype=BRACKETS;
  }
  else if(isalpha(c))
  {
    *p++=c;
    while(isalnum(c=getchar()))
    {
      *p++=c;
    }
    *p='\0';
    ungetc(c,stdin);
    return tokentype=NAME;
  }
  else
  { 
    token[0]=c;
    token[1]='\0';
    return tokentype=c;
  }
}

void skipline()
{
  int c;
  while((c=getchar())!='\n' && c!=EOF)
  {
    ;
  }
}


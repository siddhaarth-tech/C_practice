//Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100

enum{NAME,PARENS,BRACKETS};

int tokentype;
char token[MAXTOKEN];
char out[500];

int gettoken();

int main()
{
  int type;
  char temp[1000];
  
  while(gettoken()!=EOF)
  {
    strcpy(out,token);
    
    while((type=gettoken())!='\n')
    {
      if(type==PARENS || type==BRACKETS)
      {
        strcat(out,token);
      }
      else if(type=='*')
      {
        if(strchr(out,'(') || strchr(out,'['))
        {
          sprintf(temp,"(*%s)",out);
        }
        else
        {
          sprintf(temp,"*%s",out);
        }
        strcpy(out,temp);
      }
      else if(type==NAME)
      {
        sprintf(temp,"%s %s",token,out);
        strcpy(out,temp);
      }
      else
      {
        printf("invalid\n");
      }
    }
    printf("%s\n",out);
  }
  return 0;
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
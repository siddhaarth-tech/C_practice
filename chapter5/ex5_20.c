/*Exercise 5-20. Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.*/


#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100

enum{NAME,PARENS,BRACKETS,QUALIFIER};

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int gettoken();
void dcl();
void dirdcl();
void paramlist();

int main()
{
  while(gettoken()!=EOF)
  {
    strcpy(datatype,token);
    out[0]='\0';
    name[0]='\0';
    
    while(gettoken()==QUALIFIER)
    {
      strcat(datatype," ");
      strcat(datatype,token);
    }
    
    dcl();
    
    if(tokentype!='\n')
    {
      printf("syntax error\n");
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
    }
  }
  else if(tokentype==NAME)
  {
    strcpy(name,token);
  }
  else
  {
    printf("error\n");
    return ;
  }
  
  while((type=gettoken())==PARENS || type==BRACKETS || type=='(')
  {
    if(type==PARENS)
    {
      strcat(out," function returning");
    }
    else if(type=='(')
    {
      strcat(out," function taking");
      paramlist();
      strcat(out," returning");
    }
    else
    {
      strcat(out," array");
      strcat(out,token);
      strcat(out," of");
    }
  }
}


void paramlist()
{
  strcat(out," (");
  
  while(gettoken()!=')')
  {
    if(tokentype==QUALIFIER)
    {
      strcat(out,token);
      strcat(out," ");
    }
    else if(tokentype==',')
    {
      strcat(out,",");
    }
    else
    {
      strcat(out,token);
      strcat(out," ");
    }
  }
  strcat(out,")");
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
    ungetc(c,stdin);
    return tokentype='(';
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
    
    if(!strcmp(token,"const") || !strcmp(token,"volatile"))
    {
      return tokentype=QUALIFIER;
    }
    return tokentype=NAME;
  }
  else
  { 
    token[0]=c;
    token[1]='\0';
    return tokentype=c;
  }
}
/*Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define DEFAULT_N 6

struct tnode {
  char *word;
  int match;
  struct tnode *left;
  struct tnode *right;
};


int getword(char *,int);
int iskeyword(char *);
struct tnode *addtree(struct tnode *,char *);
void markgroups(struct tnode *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdup2(char *);

static struct tnode *prev=NULL;
static int prefix_len;

char *keywords[]={
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static",
    "struct","switch","typedef","union","unsigned","void","volatile","while",
    NULL
};

int main(int argc, char *argv[])
{
  struct tnode *root=NULL;
  char word[MAXWORD];

  prefix_len=(argc>1)?atoi(argv[1]):DEFAULT_N;

  while(getword(word,MAXWORD)!=EOF)
  {
    if(isalpha(word[0]) && !iskeyword(word))
    {
      root=addtree(root,word);
    }
  }
  markgroups(root);
  treeprint(root);

  return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if(p==NULL) 
  {
    p=talloc();
    p->word=strdup2(w);
    p->match=0;
    p->left=p->right=NULL;
  }
  else if((cond=strcmp(w,p->word))<0)
  {
    p->left=addtree(p->left,w);
  }
  else if (cond>0)
  {
    p->right=addtree(p->right,w);
  }

  return p;
}

void markgroups(struct tnode *p)
{
  if(p==NULL)
    return;

  markgroups(p->left);

  if(prev!=NULL && strncmp(prev->word,p->word,prefix_len)==0 && strcmp(prev->word,p->word)!=0) 
  { 
    prev->match = 1;
    p->match = 1;
  }
  prev = p;
  markgroups(p->right);
}

void treeprint(struct tnode *p)
{
  if(p!=NULL) 
  {
    treeprint(p->left);
    if(p->match)
    {
      printf("%s\n", p->word);
    }
    treeprint(p->right);
  }
}

int getword(char *word, int lim)
{
  int c, d;
  char *w=word;

  while(isspace(c=getchar()))
  {
    ;
  }
  if(c==EOF)
    return EOF;

  *w++=c;

  if(isalpha(c)) 
  {
    while(--lim > 0) 
    {
      c=getchar();
      if(!isalnum(c) && c!='_') 
      {
        ungetc(c, stdin);
        break;
      }
     *w++=c;
    }
    *w = '\0';
    return word[0];
  }

  if(c=='"') 
  {              
    while ((c=getchar())!='"' && c!=EOF)
    {
      ;
    }
  }
  else if(c=='/') 
  {           
    d=getchar();
    if(d=='*') 
    {          
      while((c=getchar())!=EOF)
        if(c=='*' && getchar()=='/')
            break;
    }
    else if(d=='/') 
    {      
      while((c=getchar())!='\n' && c!=EOF)
      {
        ;
      }
    }
    else
    {
      ungetc(d, stdin);
    }
  }

  *w = '\0';
  return c;
}

int iskeyword(char *word)
{
  for(int i=0;keywords[i]!=NULL;i++)
  {
    if(strcmp(word,keywords[i])==0)
    {
      return 1;
    }
  }
  return 0;
}

struct tnode *talloc()
{
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strdup2(char *s)
{
  char *p=(char *)malloc(strlen(s)+1);
  if(p!=NULL)
  {
    strcpy(p, s);
  }
  return p;
}



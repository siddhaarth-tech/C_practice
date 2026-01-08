/*Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and for
each word, a list of the line numbers on which it occurs. Remove noise words like ``the,''
``and,'' and so on.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct lnode {
  int lineno;
  struct lnode *next;
};

struct tnode {
  char *word;
  struct lnode *lines;
  struct tnode *left;
  struct tnode *right;
};

char *noise[]={
    "the","and","of","to","a","in","is","it","that", NULL
};

int lineno = 1;

int getword(char *, int);
int isnoise(char *);
struct tnode *addtree(struct tnode *, char *);
struct lnode *addline(struct lnode *, int);
void treeprint(struct tnode *);

int main(void)
{
  struct tnode *root=NULL;
  char word[MAXWORD];

  while(getword(word,MAXWORD)!=EOF) 
  {
    if(isalpha(word[0]) && !isnoise(word))
    {
      root=addtree(root,word);
    }
  }

  treeprint(root);
  return 0;
}

struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;
  
  if(p==NULL) 
  {
    p=malloc(sizeof(struct tnode));
    p->word=strdup(w);
    p->lines=addline(NULL,lineno);
    p->left=p->right=NULL;
  }
  else if((cond=strcmp(w,p->word))==0) 
  {
    p->lines=addline(p->lines,lineno);
  }
  else if(cond<0) 
  {
    p->left=addtree(p->left,w);
  }
  else 
  {
    p->right=addtree(p->right,w);
  }
  return p;
}

struct lnode *addline(struct lnode *p,int line)
{
  if(p==NULL) 
  {
    p = malloc(sizeof(struct lnode));
    p->lineno = line;
    p->next = NULL;
  }
  else if(p->lineno!=line) 
  {
    p->next=addline(p->next,line);
  }
  return p;
}

void treeprint(struct tnode *p)
{
  struct lnode *lp;

  if(p!=NULL) 
  {
    treeprint(p->left);
    printf("%-12s:", p->word);
    for (lp = p->lines; lp != NULL; lp = lp->next)
    {
      printf(" %d", lp->lineno);
    }
    printf("\n");
    treeprint(p->right);
  }
}

int getword(char *word, int lim)
{
  int c;
  char *w=word;

  while((c=getchar())!=EOF) 
  {
    if(c=='\n')
    {
      lineno++;
    }
    if(isalpha(c))
    {
      break;
    }
  }

  if(c==EOF)
  {
    return EOF;
  }

  *w++=c;
  while (--lim > 0) 
  {
    c=getchar();
    if(!isalnum(c)) 
    {
      ungetc(c, stdin);
      break;
    }
    *w++ = c;
  }
  *w='\0';
  return word[0];
}

int isnoise(char *w)
{
  for(int i=0;noise[i]!=NULL;i++)
  {
    if(strcmp(w,noise[i])==0)
    {
      return 1;
    }
  }
  return 0;
}


/*Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing
order of frequency of occurrence. Precede each word by its count.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXWORDS 10000

struct tnode 
{
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treestore(struct tnode *, struct tnode **, int *);
int compare(void *,void *);
struct tnode *talloc(void);
char *strdup2(const char *);


int main()
{
  struct tnode *root=NULL;
  struct tnode *list[MAXWORDS];
  char word[MAXWORD];
  int nwords=0;

  while(getword(word,MAXWORD)!=EOF)
  {
    if(isalpha(word[0]))
    {
      root=addtree(root,word);
    }
  }
  
  treestore(root,list,&nwords);

  qsort(list,nwords,sizeof(struct tnode *),compare);

  for (int i = 0; i < nwords; i++)
  {
    printf("%4d %s\n",list[i]->count,list[i]->word);
  }

  return 0;
}

struct tnode *addtree(struct tnode *p,char *w)
{
  int cond;

  if(p==NULL) 
  {
    p=talloc();
    p->word=strdup2(w);
    p->count=1;
    p->left=p->right=NULL;
  }
  else if((cond=strcmp(w,p->word))==0) 
  {
    p->count++;
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

void treestore(struct tnode *p, struct tnode **list, int *n)
{
  if(p!=NULL) 
  {
    treestore(p->left,list,n);
    list[(*n)++]=p;
    treestore(p->right,list,n);
  }
}

int compare(void *a, void *b)
{
  struct tnode *p1=*(struct tnode **)a;
  struct tnode *p2=*(struct tnode **)b;

  return p2->count-p1->count;
}

int getword(char *word,int lim)
{
  int c;
  char *w=word;

  while((c=getchar())!=EOF && !isalpha(c))
  {
    ;
  }
  if(c==EOF)
  {
    return EOF;
  }
  *w++ = c;
  while(--lim > 0) 
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


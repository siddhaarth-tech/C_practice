/*Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section. You may also find
getch and ungetch helpful.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXWORD 100
#define HASHSIZE 101

struct node 
{
  struct node *next;
  char *name;
  char *defn;
};

static struct node *hashtable[HASHSIZE];

int getword(char *,int max);
int getch();
void ungetch(int val);
unsigned hash(char *s);
struct node *lookup(char *s);
struct node *install(char *name,char *defn);

int main()
{
  char word[MAXWORD];
  char name[MAXWORD];
  char defn[MAXWORD];
  struct node *np;

  while(getword(word,MAXWORD)!=EOF) 
  {
    if (strcmp(word, "#define") == 0) 
    {
      getword(name,MAXWORD);
      getword(defn,MAXWORD);
      install(name,defn);
      
      int c;
      while((c=getch())!='\n' && c!=EOF)
      {
        ;
      }
    }
    else if(isalpha(word[0]) && (np=lookup(word))!=NULL) 
    {
      printf("%s", np->defn);
    }
    else 
    {
      printf("%s", word);
    }
  }
  return 0;
}

unsigned hash(char *s)
{
  unsigned hashval=0;
  
  while(*s!='\0')
  {
    hashval=*s + 31 * hashval;
    s++;
  }
  return hashval % HASHSIZE;
}

struct node *lookup(char *s)
{
  struct node *np;
  np=hashtable[hash(s)];
  while(np!=NULL)
  {
    if(strcmp(s,np->name)==0)
    {
      return np;
    }
    np=np->next;
  }
  return NULL;
}

struct node *install(char *name,char *defn)
{
  struct node *np;
  unsigned hashval;
  
  if((np=lookup(name))==NULL)
  {
    np=(struct node*)malloc(sizeof(*np));
    if(np==NULL)
    {
      return NULL;
    }
    np->name=strdup(name);
    if(np->name==NULL)
    {
      return NULL;
    }
    
    hashval=hash(name);
    np->next=hashtable[hashval];
    hashtable[hashval]=np;
  }
  else
  {
    free(np->defn);
  }
  np->defn=strdup(defn);
  if(np->defn==NULL)
  {
    return NULL;
  }
  
  return np;
}



int getword(char *word,int lim)
{
  int c;
  char *w = word;

  while(isspace(c=getch()))
  {
    ;
  }

  if(c==EOF)
  {
    return EOF;
  }

  *w++=c;

  if(!isalpha(c) && c!='#') 
  {
    *w='\0';
    return c;
  }

  while(--lim>0) 
  {
    c=getch();
    if(!isalnum(c)) 
    {
      ungetch(c);
      break;
    }
    *w=c;
    w++;
  }
  *w = '\0';
  return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp=0;

int getch(void)
{
    return (bufp>0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp<BUFSIZE)
    {
      buf[bufp++] = c;
    }    
}

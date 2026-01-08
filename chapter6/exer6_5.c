/*Exercise 6-5. Write a function undef that will remove a name and definition from the table
maintained by lookup and install.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASHSIZE 101

struct node 
{
  struct node *next;
  char *name;
  char *defn;
};

static struct node *hashtable[HASHSIZE];

unsigned hash(char *s);
struct node *lookup(char *s);
struct node *install(char *name,char *defn);
void undef(char *name);

int main()
{
  install("IN","1");
  install("OUT","0");
  install("MAX","100");
  
  printf("IN = %s\n",lookup("IN")->defn);
  printf("OUT = %s\n",lookup("OUT")->defn);
  
  undef("IN");
  
  if(lookup("IN")==NULL)
  {
    printf("IN undefined\n");
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

void undef(char *name)
{
  struct node *np,*prev;
  unsigned hashval;
  
  hashval=hash(name);
  np=hashtable[hashval];
  prev=NULL;
  
  while(np!=NULL)
  {
    if(strcmp(np->name,name)==0)
    {
      if(prev==NULL)
      {
        hashtable[hashval]=np->next;
      }
      else
      {
        prev->next=np->next;
      }
      free(np->name);
      free(np->defn);
      free(np);
      return;
    }
    prev=np;
    np=np->next;
  }
}

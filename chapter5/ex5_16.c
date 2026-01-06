/*Exercise 5-16. Add the -d (``directory order'') option, which makes comparisons only on
letters, numbers and blanks. Make sure it works in conjunction with -f.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXLINES 1000
#define MAX 100
#define BUFSIZE 10000

int getlines(char **lineptr,int max);
int my_getline(char *s,int max);
void my_qsort(void *lineptr[],int left,int right,int (*comp)(void *,void *),int reverse);
void swap(void *v[],int i,int j);
int numcmp(char *s,char *t);
int foldcmp(char *s1,char *s2);
void writelines(char **lineptr,int nlines);
char *alloc(int len);
int dircmp(char *s1,char *s2,int fold);

int fold=0;

int main(int argc,char *argv[])
{
  char *lineptr[MAXLINES];
  int numeric=0;
  int reverse=0;
  int directory=0;
  while(--argc>0 && *(++argv)[0]=='-')
  {
    char *p= *argv+1;
    while(*p)
    {
      switch(*p++)
      {
        case 'n':
          numeric =1;
          break;
        case 'r':
          reverse=1;
          break;
        case 'f':
          fold=1;
          break;
        case 'd':
          directory=1;
          break;
        default:
          printf("invalid");
          return 1;
      }
    }
  }
  int nlines;
  if((nlines=getlines(lineptr,MAXLINES))>0)
  {
    int (*cmp)(void *,void *);
    
    if(numeric)
    {
      cmp=(int (*)(void *,void *)) numcmp;
    }
    else if(fold)
    {
      cmp=(int (*)(void *,void *)) foldcmp;
    }
    else if(directory)
    { 
      cmp=(int (*)(void *,void *)) dircmp;
    }
    else 
    {
      cmp=(int (*)(void *,void *)) strcmp;
    }
    
    my_qsort((void **)lineptr,0,nlines-1,cmp,reverse);
    writelines(lineptr,nlines);
  }
  else
  {
    printf("there are no lines ");
    return 1;
  }
  return 0;
}

int dircmp(char *s1,char *s2,int fold)
{
  int c1,c2;
  
  while(*s1 || *s2)
  {
    while(*s1 && !isalnum(*s1) && *s1!=' ')
    {
      s1++;
    }
    while(*s2 && !isalnum(*s2) && *s2!=' ')
    {
      s2++;
    }
    
    c1=*s1;
    c2=*s2;
    if(fold)
    {
      c1=tolower(c1);
      c2=tolower(c2);
    }
    
    if(c1!=c2)
    {
      return c1-c2;
    }
    if(*s1) s1++;
    if(*s2) s2++;
  }
  return 0;
}

int foldcmp(char *s1,char *s2)
{
  int c1,c2;
  
  while(*s1 || *s2)
  {
    c1=tolower(*s1);
    c2=tolower(*s2);
    
    if(c1!=c2)
    {
      return c1-c2;
    }
    
    if(*s1)
    {
      s1++;
    }
    if(*s2)
    {
      s2++;
    }
  }
  return 0;
}

void writelines(char **lineptr,int nlines)
{
  for(int i=0;i<nlines;i++)
  {
    printf("%s  ",lineptr[i]);
  }
}

void my_qsort(void *v[],int left,int right,int (*comp)(void *,void *),int reverse)
{
  int last,i;
  
  if(left>=right)
  {
    return;
  }
  swap(v,left,(left+right)/2);
  last=left;
  
  for(int i=left+1;i<=right;i++)
  {
    int cmp=(*comp)(v[i],v[left]);
    
    if(reverse)
    {
      cmp=-cmp;
    }
    
    if(cmp<0)
    {
      swap(v,++last,i);
    }
  }
  
  swap(v,left,last);
  my_qsort(v,left,last-1,comp,reverse);
  my_qsort(v,last+1,right,comp,reverse);
}

void swap(void *v[],int i,int j)
{
  char *temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}

int numcmp(char *s1,char *s2)
{
  double num1=atof(s1);
  double num2=atof(s2);
  
  if(num1<num2)
  {
    return -1;
  }
  else if(num1>num2)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int getlines(char **lineptr,int max)
{
  char line[MAX];
  int nline=0;
  int len;
  char *p;
  while((len=my_getline(line,MAX))>0)
  {
    if(nline>=max || (p=alloc(len))==NULL)
    {
      return -1;
    }
    line[len-1]='\0';
    strcpy(p,line);
    lineptr[nline]=p;
    nline++;
  }
  return nline;
}

char *alloc(int len)
{
  static char allocbuf[BUFSIZE];
  static char *allocp=allocbuf;
  
  if(allocbuf + BUFSIZE - allocp >= len)
  {
    allocp=allocp+len;
    return allocp-len;
  }
  else
  {
    return NULL;
  }
}

int my_getline(char *s,int max)
{
  int c;
  char *start=s;
  while(--max>0 && (c=getchar())!=EOF && c!='\n')
  {
    *s=c;
    s++;
  }
  if(c=='\n')
  {
    *s='\n';
    s++;
  }
  *s='\0';
  
  return s - start;
}

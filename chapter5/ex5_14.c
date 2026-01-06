/*Exercise 5-14. Modify the sort program to handle a -r flag, which indicates sorting in reverse
(decreasing) order. Be sure that -r works with -n.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINES 1000
#define MAX 100
#define BUFSIZE 10000

int getlines(char **lineptr,int max);
int my_getline(char *s,int max);
void my_qsort(void *lineptr[],int left,int right,int (*comp)(void *,void *),int reverse);
void swap(void *v[],int i,int j);
int numcmp(char *s,char *t);
void writelines(char **lineptr,int nlines);
char *alloc(int len);

int main(int argc,char *argv[])
{
  char *lineptr[MAXLINES];
  int numeric=0;
  int reverse=0;
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



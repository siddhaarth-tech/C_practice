//Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster is the program?

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 1000
#define MAXLEN 100
#define STORAGE 10000

int readlines(char *lineptr[],char *storage,int maxline);
int my_getline(char *line,int max);
void writelines(char *lineptr[],int nlines);
void my_qsort(char *v[],int left,int right);
void swap(char *v[],int i,int j);

int main()
{
  char storage[STORAGE];
  char *lineptr[MAXLINE];
  
  int nlines = readlines(lineptr,storage,MAXLINE);
  
  if(nlines<0)
  {
    printf("limit reached\n");
    return 1;
  }
  
  my_qsort(lineptr,0,nlines-1);
  writelines(lineptr,nlines);
  
  return 0;
}

int readlines(char *lineptr[],char *storage,int max)
{
  int len;
  int nlines=0;
  char line[MAXLEN];
  char *p=storage;
  while((len=my_getline(line,MAXLEN))>0)
  {
    if(nlines>=MAXLINE || p+len>=storage+STORAGE)
    {
      return -1;
    }
    
    line[len-1]='\0';
    strcpy(p,line);
    lineptr[nlines]=p;
    nlines++;
    p=p+len;
  }
  return nlines;
}

int my_getline(char *s,int max)
{
  char *start=s;
  int c;
  
  while(max>0 && (c=getchar())!=EOF && c!='\n')
  {
    *s=c;
    s++;
    max--;
  }
  
  if(c=='\n')
  {
    *s='\n';
    s++;
  }
  
  *s='\0';
  return s-start;
}

void writelines(char *lineptr[],int nlines)
{
  while(nlines>0)
  {
    printf("%s\n",*lineptr++);
    nlines--;
  }
}

void my_qsort(char *v[],int left,int right)
{
  int i,last;
  
  if(left>=right)
  {
    return;
  }
  
  swap(v,left,(left+right)/2);
  last=left;
  
  for(i=left+1;i<=right;i++)
  {
    if(strcmp(v[i],v[left])<0)
    {
      swap(v,++last,i);
    }
  }
  
  swap(v,left,last);
  my_qsort(v,left,last-1);
  my_qsort(v,last+1,right);
}

void swap(char *v[],int i,int j)
{
  char *temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}
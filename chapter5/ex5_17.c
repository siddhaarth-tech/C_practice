/*Exercise 5-17. Add a field-searching capability, so sorting may bee done on fields within
lines, each field sorted according to an independent set of options. (The index for this book
was sorted with -df for the index category and -n for the page numbers.)*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAXLINES 10000
#define MAXLEN 1000
#define BUFSIZE 10000

struct field
{
  int fieldno;
  int numeric;
  int fold;
  int directory;
  int reverse;
};

int readlines(char *lineptr[],int maxlines);
void writelines(char *lineptr[],int nlines);
void my_qsort(void *v[],int left,int right,int (*comp)(void *,void *),int reverse);
int fieldcmp(void *a,void *b);
char *getfield(char *line,int fieldno);
char *alloc(int n);

char *lineptr[MAXLINES];
struct field f={1,0,0,0,0};

int main(int argc,char *argv[])
{
  int nlines;
  
  while(--argc>0 && (*++argv)[0]=='-')
  {
    char *p=argv[0]+1;
    while(*p)
    {
      switch(*p++)
      {
        case 'k':
          f.fieldno=atoi(*++argv);
          argc--;
          break;
        case 'n':
          f.numeric=1;
          break;
        case 'f':
          f.fold=1;
          break;
        case 'd':
          f.directory=1;
          break;
        case 'r':
          f.reverse=1;
          break;
        default:
          printf("invalid\n");
          return 1;
      }
    }
  }
  
  if((nlines=readlines(lineptr,MAXLINES))<0)
  {
    printf("invalid");
    return 1;
  }
  
  my_qsort((void **) lineptr,0,nlines-1,fieldcmp,f.reverse);
  
  writelines(lineptr,nlines);
  
  return 0;
}

int fieldcmp(void *a,void *b)
{
  char f1[MAXLEN],f2[MAXLEN];
  char *s1,*s2;
  int c1,c2;
  
  strcpy(f1,getfield((char *)a,f.fieldno));
  strcpy(f2,getfield((char *)b,f.fieldno));
  
  if(f.numeric)
  {
    double v1=atof(f1);
    double v2=atof(f2);
    if(v1<v2) 
    {
      return -1;
    }
    if(v1>v2)
    {
      return 1;
    }
    return 0;
  }
  
  s1=f1;
  s2=f2;
  
  while(*s1 || *s2)
  {
    c1=*s1;
    c2=*s2;
    
    if(f.directory)
    {
      while(c1 && !isalnum(c2) && c1!=' ')
      {
        s1++;
        c1=*s1;
      }
      while(c2 && !isalnum(c2) && c2!=' ')
      {
        s2++;
        c2=*s2;
      }
    }
      if(f.fold)
      {
        c1=tolower(c1);
        c2=tolower(c2);
      }
      
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

char *getfield(char *line,int fieldno)
{
  static char buf[MAXLEN];
  int i=1;

  while(*line && i<fieldno) 
  {
    while(*line && *line!=' ' && *line!='\t')
    {       
      line++;
    }
    while(*line==' ' || *line=='\t')
    {
      line++;
    }
    i++;
  }

  int j=0;
  while(*line && *line!=' ' && *line!='\t')
  {
    buf[j++]=*line++;
  }
  buf[j]='\0';
  return buf;
}


void my_qsort(void *v[],int left,int right,int (*comp)(void *,void *),int reverse)
{
  int i,last;
  
  if(left>=right)
  {
    return;
  }
  
  void swap(void *v[],int left,int right);
  
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
  void*temp=v[i];
  v[i]=v[j];
  v[j]=temp;
}

int readlines(char *lineptr[],int maxlines)
{
  int len,nlines=0;
  char *p,line[MAXLEN];
  
  while(fgets(line,MAXLEN,stdin))
  {
    len=strlen(line);
    if(nlines>=maxlines || (p=alloc(len+1))==NULL)
    {
      return -1;
    }
    strcpy(p,line);
    lineptr[nlines++]=p;
  }
  return nlines;
}

void writelines(char *lineptr[],int nlines)
{
  while(nlines-- >0)
  {
    printf("%s",*lineptr++);
  }
}

char *alloc(int n)
{
  static char allocbuf[BUFSIZE];
  static char *allocp=allocbuf;
  
  if(allocbuf+BUFSIZE-allocp>=n)
  {
    allocp=allocp+n;
    return allocp-n;
  }
  else
  {
    return NULL;
  }
}

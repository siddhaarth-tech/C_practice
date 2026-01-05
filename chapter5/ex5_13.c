/*Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that
tail -n
prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n. Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size.*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 1000
#define DEFAULT 10
#define BUFSIZE 10000

int my_getline(char *s,int max);
char *alloc(int n);

int main(int argc,char *argv[])
{
  int n=DEFAULT;
  if(argc==2 && argv[1][0]=='-')
  {
    n=atoi(argv[1]+1);
  }
  
  if(n<=0)
  {
    n=DEFAULT;
  }
  char **lineptr=malloc(n * sizeof(char *));
  if(lineptr==NULL)
  {
    printf("memory allocation failed ");
    return 1;
  }
  
  char line[MAX];
  int count=0;
  while(my_getline(line,MAX)>0)
  {
    int index=count%n;
    
    if(count>=n && lineptr[index]!=NULL)
    {
      free(lineptr[index]);
    }
    
    lineptr[index]=malloc(strlen(line)+1);
    if(lineptr[index]==NULL)
    {
      printf("out of memory ");
      return 1;
    }
    strcpy(lineptr[index],line);
    count++;
  }
  
  int start= (count>n)?count%n : 0;
  int total= (count<n)?count:n;
  
  for(int i=0;i<total;i++)
  {
    int ind=(start+i)%n;
    printf("%s",lineptr[ind]);
    free(lineptr[ind]);
  }
  
  free(lineptr);
  return 0;
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

char *alloc(int n)
{
  static char allocbuf[BUFSIZE];
  static char *allocp=allocbuf;
  
  if(allocbuf + BUFSIZE - allocp >=n)
  {
    allocp=allocp+n;
    return allocp-n;
  }
  else
  {
    return NULL;
  }
}

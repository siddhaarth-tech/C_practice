/*Exercise 5-11. Modify the program en tab and detab (written as exercises in Chapter 1) to
accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.*/

//Detab

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100
#define DEFAULT 8

int next_tab(int col,int *tab,int ntabs);

int main(int argc,char *argv[])
{
  int col=0;
  int tab[MAX];
  int ntabs=0;
  for(int i=1;i<argc && i<MAX;i++)
  {
    tab[ntabs]=atoi(argv[i]);
    ntabs++;
  }
  int c;
  while((c=getchar())!=EOF)
  {
    if(c=='\t')
    {
      int next=next_tab(col,tab,ntabs);
      while(col<next)
      {
        putchar(' ');
        col++;
      }
    }
    else if(c=='\n')
    {
      putchar('\n');
      col=0;
    }
    else
    { 
      putchar(c);
      col++;
    }
  }
  return 0;
}


int next_tab(int col,int *tab,int ntabs)
{
  for(int i=0;i<ntabs;i++)
  {
    if(col<tab[i])
    {
      return tab[i];
    }
  }
  
  return ((col/DEFAULT)+1) * DEFAULT;
}
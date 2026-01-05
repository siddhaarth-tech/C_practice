/*Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to
accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.*/

//entab

#include<stdio.h>
#include<stdlib.h>

#define MAX 100
#define DEFAULT 8

int next_tab(int col,int *tab,int ntabs);

int main(int argc,char *argv[])
{
  int tab[MAX];
  int ntabs=0;
  for(int i=1;i<argc && i<MAX;i++)
  {
    tab[ntabs]=atoi(argv[i]);
    ntabs++;
  }
  int spacecount=0;
  int col=0;
  int c;
  while((c=getchar())!=EOF)
  {
    if(c==' ')
    {
      spacecount++;
    }
    else
    {
      while(spacecount>0)
      {
        int next=next_tab(col,tab,ntabs);
        int to_tab=next-col;
        
        if(spacecount>=to_tab)
        {
          putchar('\t');
          spacecount=spacecount-to_tab;
          col=next;
        }
        else
        {
          putchar(' ');
          spacecount--;
          col++;
        }
      }
      if(c=='\n')
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
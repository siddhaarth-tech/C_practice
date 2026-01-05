/*Exercise 5-12. Extend entab to accept the shorthand
entab -m +n
to mean tab stops every n columns, starting at column m. Choose convenient (for the user)
default behavior.*/

#include<stdio.h>
#include<stdlib.h>

#define DEFAULT 8

int next_tab(int col,int start,int step);

int main(int argc,char *argv[])
{
  int step=DEFAULT;
  int start=0;
  for(int i=1;i<argc;i++)
  {
    if(argv[i][0]=='-')
    {
      start=atoi(argv[i]+1);
    }
    else if(argv[i][0]=='+')
    {
      step=atoi(argv[i]+1);
    }
  }
  int col=0;
  int spacecount=0;
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
        int next=next_tab(col,start,step);
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

int next_tab(int col,int start,int step)
{
  if(col<start)
  {
    return start;
  }
  
  return start + ((col-start)/step + 1)*step;
}

/*Exercise 7-8. Write a program to print a set of files, starting each new one on a new page,
with a title and a running page count for each file.*/

#include <stdio.h>

#define MAXLINE 1000
#define LINES_PER_PAGE 5

void print_file(char *filename)
{
  FILE *fp;
  char line[MAXLINE];
  int linecount=0;
  int page=1;

  fp=fopen(filename,"r");
  if(fp==NULL) 
  {
    printf("error in opening file");
    return;
  }

  printf("\nfile: %s    page %d\n", filename, page);
  printf("--------------------\n");

  while(fgets(line,MAXLINE,fp)!=NULL) 
  {
    if(linecount==LINES_PER_PAGE) 
    {
      page++;
      linecount = 0;
      printf("\nfile: %s   page %d\n",filename,page);
      printf("--------------------\n");
    }
    printf("%s",line);
    linecount++;
  }

  fclose(fp);
}

int main(int argc,char *argv[])
{
  int i;

  if(argc<2) 
  {
    printf("invalid\n");
    return 1;
  }

  for(i=1;i<argc;i++)
  {
    print_file(argv[i]);
  }
  return 0;
}


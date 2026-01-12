/*Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input from a set of
named files or, if no files are named as arguments, from the standard input. Should the file
name be printed when a matching line is found?*/

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc,char *argv[])
{
  FILE *fp;
  char line[MAXLINE];
  char *pattern;

  if(argc<2) 
  {
    printf("invalid\n");
    return 1;
  }

  pattern=argv[1];

  if(argc==2) 
  {
    while (fgets(line, MAXLINE, stdin) != NULL) 
    {
      if(strstr(line, pattern)!=NULL)
      {
         printf("%s", line);
      }          
    }
  }
  else 
  {
    int i;
    for (i=2;i<argc;i++) 
    {
      fp=fopen(argv[i],"r");
      if (fp==NULL)
      {
        printf("Cannot open file");
        continue;
      }
      while(fgets(line,MAXLINE,fp)!=NULL) 
      {
        if(strstr(line,pattern)!=NULL)
        {
          printf("%s: %s",argv[i],line);
        }          
      }
      fclose(fp);
    }
  }

  return 0;
}

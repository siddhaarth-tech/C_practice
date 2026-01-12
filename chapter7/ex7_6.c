//Exercise 7-6. Write a program to compare two files, printing the first line where they differ.

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc,char *argv[])
{
  FILE *fp1,*fp2;
  char line1[MAXLINE],line2[MAXLINE];
  int lineno=1;

  if(argc!=3) 
  {
    printf("invalid\n");
    return 1;
  }

  fp1=fopen(argv[1],"r");
  fp2=fopen(argv[2],"r");

  if (fp1==NULL || fp2==NULL) 
  {
    printf("Error\n");
    return 1;
  }

  while(1) 
  {
    char *l1=fgets(line1,MAXLINE,fp1);
    char *l2=fgets(line2,MAXLINE,fp2);

    if(l1==NULL && l2==NULL) 
    {
      printf("files are same\n");
      break;
    }
    if(l1==NULL || l2==NULL)
    {
      printf("files differ at line %d\n",lineno);
      break;
    }
    if(strcmp(line1,line2)!=0) 
    {
      printf("files differ at line %d\n",lineno);
      printf("file1: %s",line1);
      printf("file2: %s",line2);
      break;
    }
    lineno++;
  }

  fclose(fp1);
  fclose(fp2);

  return 0;
}

/*Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close
instead of their standard library equivalents. Perform experiments to determine the relative
speeds of the two versions.*/


#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define BUFSIZE 1024

int main(int argc,char* argv[])
{
  int fd;
  char buffer[BUFSIZE];
  
  if(argc==1)
  {
    fd=0;
  }
  else
  {
    fd=open(argv[1],O_RDONLY,0);
    if(fd==-1)
    {
      printf("error");
      return 1;
    }
  }
  int n;
  while((n=read(fd,buffer,BUFSIZE))>0)
  {
    write(1,buffer,n);
  }
  if(fd!=0)
  {
    close(fd);
  }
  return 0;
}
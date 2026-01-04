/*Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.*/

#include<stdio.h>
void itoa(int n,char s[],int *i);
int main()
{
  int n;
  char s[100];
  printf("enter the number : ");
  scanf("%d",&n);
  int i=0;
  if(n<0)
  {
    s[i]='-';
    i++;
    n=-n;
  }
  itoa(n,s,&i);
  s[i]='\0';
  printf("%s\n",s);
  return 0;
}

void itoa(int n,char s[],int *i)
{
  if(n/10)
  {
    itoa(n/10,s,i);
  }
  s[(*i)++]=(n%10)+'0';
}
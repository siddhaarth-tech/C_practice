/*Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).*/

//pointer version itoa

#include<stdio.h>

void my_itoa(int n,char *s);
void reverse(char *s);

int main()
{
  int n;
  char s[100];
  printf("enter the number : ");
  scanf("%d",&n);
  
  my_itoa(n,s);
  reverse(s);
  printf("the number after converted to string : %s\n",s);
  
  return 0;
}

void my_itoa(int n,char *s)
{
  int sign=n;
  
  if(n<0)
  {
    n=-n;
  }
  
  do
  {
    *s=(n%10) + '0';
    s++;
    n=n/10;
  }while(n>0);
  
  if(sign<0)
  {
    *s='-';
  }
}

void reverse(char *s)
{
  char *end=s;
  
  while(*end!='\0')
  {
    end++;
  }
  end--;
  
  while(s<end)
  {
    char temp=*s;
    *s=*end;
    *end=temp;
    
    s++;
    end--;
  }
}

/*Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa,
and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop
(Chapter 4).*/

//strindex
#include<stdio.h>

int my_strind(char *s,char *t);

int main()
{
  char s[100];
  char t[100];
  
  printf("enter the string s : ");
  fgets(s,sizeof(s),stdin);
  
  printf("enter the string t : ");
  fgets(t,sizeof(t),stdin);
  
  int result = my_strind(s,t);
  
  if(result==-1)
  {
    printf("not found");
  }
  else
  {
    printf("the string t found at ind %d in string s \n",result);
  }
  return 0;
}

int my_strind(char *s,char *t)
{
  char *p,*q,*r;
  
  p=s;
  while(*p!='\0')
  {
    q=p;
    r=t;
    while(*r!='\0' && *q==*r)
    {
      r++;
      q++;
    }
    if(*r=='\0')
    {
      return p - s;
    }
    p++;
  }
  return -1;
}
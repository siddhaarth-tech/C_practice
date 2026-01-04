//Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the string s in place.

#include<stdio.h>
#include<string.h>
void reverse(char s[],int left,int right);
int main()
{
  char s[100];
  printf("enter the string : ");
  scanf("%s",s);
  int len=strlen(s);
  reverse(s,0,len-1);
  printf("%s\n",s);
  return 0;
}
void reverse(char s[],int left,int right)
{
  if(left>=right)
  {
    return;
  }
  
  char temp=s[left];
  s[left]=s[right];
  s[right]=temp;
  
  reverse(s,left+1,right-1);
}
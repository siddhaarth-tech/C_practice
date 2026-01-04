//Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)

#include<stdio.h>
#define swap(t,a,b) {t temp=a; a=b; b=temp;}
int main()
{
  int a=10;
  int b=5;
  swap(int,a,b);
  printf("the value of a : %d,the value of b : %d\n",a,b);
  
  double x=7.6;
  double y=5.4;
  swap(double,x,y);
  printf("the value of x : %f,the value of y : %f\n",x,y);
  return 0;
}

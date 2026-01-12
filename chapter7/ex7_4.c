/*Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous
section.*/


#include <stdio.h>
#include <stdarg.h>

int minscanf(char *fmt, ...)
{
  va_list ap;
  int result;

  va_start(ap, fmt);
  result=vscanf(fmt, ap);
  va_end(ap);

  return result;
}

int main()
{
  int x;
  float y;
  char name[20];

  printf("enter int,float and name: ");
  if(minscanf("%d %f %s", &x, &y, name) == 3) 
  {
    printf("you entered:\n");
    printf("x = %d\n", x);
    printf("y = %.2f\n", y);
    printf("name = %s\n", name);
  } 
  else 
  {
    printf("invalid input\n");
  }

  return 0;
}

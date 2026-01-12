/*Exercise 7-9. Functions like isupper can be implemented to save space or to save time.
Explore both possibilities.*/


#include<stdio.h>

int my_isupper_space(int c)
{
  return (c>='A' && c<='Z');
}

int my_isupper_time(int c)
{
  static int table[128] = {0};
  static int initialized = 0;

  if(!initialized) 
  {
    int i;
    for(i='A';i<='Z';i++)
    {
      table[i]=1;
    }
    initialized=1;
  }

  return table[c];
}

int main()
{
  char test_chars[]={'A','Z','a','z','5'};
  int i;
  for(i=0;i<5;i++) 
  {
    char c=test_chars[i];

    printf("character '%c'\n", c);
    printf("space-saving: %d\n", my_isupper_space(c));
    printf("time-saving: %d\n\n", my_isupper_time(c));
  }

  return 0;
}

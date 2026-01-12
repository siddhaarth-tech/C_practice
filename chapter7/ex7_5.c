/*Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do
the input and number conversion.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVAL 100   
#define MAXTOK 100   

int sp = 0;     
double val[MAXVAL];

void push(double f)
{
  if(sp<MAXVAL)
    val[sp++] = f;
  else
    printf("error\n");
}

double pop()
{
  if(sp>0)
    return val[--sp];
  else 
  {
    printf("error\n");
    return 0.0;
  }
}

int main()
{
  char token[MAXTOK];
  double x,op2;

  printf("postfix calculator\n");

  while(scanf("%s",token)==1) 
  {
    if (sscanf(token, "%lf", &x) == 1)
        push(x);
    else
    {
      switch (token[0]) 
      {
        case '+':
          push(pop() + pop());
          break;

        case '*':
          push(pop() * pop());
          break;

        case '-':
          op2 = pop();
          push(pop() - op2);
          break;

        case '/':
          op2 = pop();
          if (op2 != 0.0)
            push(pop() / op2);
          else
            printf("error\n");
            break;

        case '=':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error%s\n", token);
            break;
      }
    }
  }

  return 0;
}

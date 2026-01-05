/*Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 100

void push(double val);
double pop();

double stack[MAX];
int sp=0;

int main(int argc,char *argv[])
{
  double op2;
  for(int i=1;i<argc;i++)
  {
    if(isdigit(argv[i][0]) || (argv[i][0]=='-' && isdigit(argv[i][1])))
    {
      push(atof(argv[i]));
    }
    else
    {
      switch(argv[i][0])
      {
        case '+':
          push(pop()+pop());
          break;
        case '*':
          push(pop()*pop());
          break;
        case '-':
          op2=pop();
          push(pop()-op2);
          break;
        case '/':
          op2=pop();
          if(op2!=0)
          {
            push(pop()/op2);
          }
          else
          {
            printf("divide by zero error\n");
          }
          break;
        default:
          printf("invalid expression\n");
          return 1;
      }
    }
  }
  if(sp==1)
  {
    printf("the final result is %f\n",pop());
  }
  else
  {
    printf("No elements in stack\n");
  }
  return 0;
}

void push(double val)
{
  if(sp<MAX)
  {
    stack[sp]=val;
    sp++;
  }
  else
  {
    printf("overflow");
  }
}

double pop()
{
  if(sp>0)
  {
    sp--;
    return stack[sp];
  }
  else
  {
    printf("underflow");
    return 0.0;
  }
}

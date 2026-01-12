/*Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
expr 2 3 4 + *
evaluates 2 * (3+4).*/
/* Exercise 5-10: Reverse Polish Expression Evaluator */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

void push(double val);
double pop(void);

double stack[MAX];
int sp = 0;

int main(int argc, char *argv[])
{
    double op2;

    if (argc < 2) {
        printf("No elements in stack\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {

        /* number (positive or negative) */
        if (isdigit((unsigned char)argv[i][0]) ||
           (argv[i][0] == '-' && isdigit((unsigned char)argv[i][1]) && argv[i][2] == '\0')) {

            push(atof(argv[i]));
        }
        /* operator must be a single character */
        else if (argv[i][1] == '\0') {

            switch (argv[i][0]) {

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
                    else {
                        printf("divide by zero error\n");
                        return 1;
                    }
                    break;

                default:
                    printf("invalid operator: %s\n", argv[i]);
                    return 1;
            }
        }
        else {
            printf("invalid argument: %s\n", argv[i]);
            return 1;
        }
    }

    if (sp == 1)
        printf("the final result is %f\n", pop());
    else
        printf("invalid RPN expression\n");

    return 0;
}

/* stack operations */

void push(double val)
{
    if (sp < MAX)
        stack[sp++] = val;
    else
        printf("stack overflow\n");
}

double pop(void)
{
    if (sp > 0)
        return stack[--sp];
    else {
        printf("stack underflow\n");
        return 0.0;
    }
}

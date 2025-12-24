/*Exercise 4-4. Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* maximum depth of stack */
#define BUFSIZE 100

/* stack */
int sp = 0;
double val[MAXVAL];

/* buffer for getch/ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* function declarations */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);


int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;

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
                printf("error: zero divisor\n");
            break;

        case '?':   /* print top */
            print_top();
            break;

        case 'd':   /* duplicate top */
            duplicate_top();
            break;

        case 's':   /* swap top two */
            swap_top();
            break;

        case 'c':   /* clear stack */
            clear_stack();
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %c\n", type);
            break;
        }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* print top element without popping */
void print_top(void)
{
    if (sp > 0)
        printf("Top element: %.8g\n", val[sp - 1]);
    else
        printf("Stack empty\n");
}

/* duplicate top element */
void duplicate_top(void)
{
    if (sp > 0)
        push(val[sp - 1]);
    else
        printf("Stack empty\n");
}

/* swap top two elements */
void swap_top(void)
{
    if (sp >= 2) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("Not enough elements to swap\n");
    }
}

/* clear the stack */
void clear_stack(void)
{
    sp = 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    i = 0;

    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';
        }
        s[++i] = next;
        c = next;
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    return NUMBER;
}

/* getch: get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
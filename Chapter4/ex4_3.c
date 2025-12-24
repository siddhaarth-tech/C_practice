/*Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add
the modulus (%) operator and provisions for negative numbers.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100     /* max size of operand */
#define NUMBER  '0'     /* signal that a number was found */
#define MAXVAL  100     /* max depth of stack */

/* stack */
int sp = 0;
double val[MAXVAL];

/* function prototypes */
int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int c);

/* MAIN  */
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

        case '%':      /* MODULUS */
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero divisor\n");
            break;

        case '\n':
            printf("\t%.8g\n", pop());
            break;

        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

/*  STACK FUNCTIONS  */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full\n");
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/*  INPUT HANDLING  */
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = c;
    else
        printf("ungetch: too many characters\n");
}

/*GETOP  */
int getop(char s[])
{
    int i, c;

    /* skip whitespace */
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    /* check for negative number */
    if (c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return '-';
        }
        s[1] = next;
        i = 1;
        c = next;
    } else if (!isdigit(c) && c != '.') {
        return c;
    } else {
        i = 0;
    }

    /* collect integer part */
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    /* collect fraction part */
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    return NUMBER;
}
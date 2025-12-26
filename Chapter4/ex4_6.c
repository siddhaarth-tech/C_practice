/* Exercise 4-6: Add commands for handling variables. (It's easy to provide twenty-six variables
with single-letter names.) Add a variable for the most recently printed value*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

double vars[26];        // Variables A–Z
double last = 0.0;      // Last printed value

int sp = 0;             // Stack pointer
double val[MAXVAL];     // Value stack

char buf[BUFSIZE];      // Input buffer
int bufp = 0;           // Buffer pointer

int getop(char s[]);
void push(double val);
double pop();
int getch();
void ungetch(int val);

int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int var = 0;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
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
                if (op2 != 0)
                    push(pop() / op2);
                else
                    printf("divide by zero\n");
                break;

            case '=':
                pop();
                vars[var] = pop();
                push(vars[var]);
                break;

            case '\n':
                last = pop();
                printf("%.8g\n", last);
                break;

            default:
                if (isupper(type))
                {
                    var = type - 'A';
                    push(vars[var]);
                }
                else if (type == '_')
                    push(last);
                else
                    printf("invalid\n");
                break;
        }
    }
    return 0;
}

void push(double value)
{
    if (sp < MAXVAL)
        val[sp++] = value;
    else
        printf("overflow\n");
}

double pop()
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("underflow\n");
        return 0.0;
    }
}

int getop(char s[])
{
    int i = 0, c, next;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    s[0] = c;
    s[1] = '\0';

    if (isupper(c) || c == '_' || c == '=')
        return c;

    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    if (c == '-')
    {
        next = getch();
        if (!isdigit(next) && next != '.')
        {
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

int getch()
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int value)
{
    if (bufp < BUFSIZE)
        buf[bufp++] = value;
    else
        printf("overflow\n");
}

#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */

// hello everyone
int main()
{
    int c, nl, nw, nc, state;
    char str[]="hello///* count lines, words, and characters in input */";
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("/*efieef*/%d %d %d\n", nl, nw, nc);
}

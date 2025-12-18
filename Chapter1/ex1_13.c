/*Write a program to print a histogram of the lengths of words in its input. It is
easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging*/

#include <stdio.h>

#define MAXLEN 20

int main() {
    int ch, length = 0;
    int count[MAXLEN] = {0};

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (length > 0 && length < MAXLEN)
                count[length]++;
            length = 0;
        } else {
            length++;
        }
    }

    if (length > 0 && length < MAXLEN)
        count[length]++;

    /* Horizontal histogram */
    printf("\nHorizontal Histogram:\n");
    for (int i = 1; i < MAXLEN; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < count[i]; j++)
            putchar('*');
        putchar('\n');
    }

    int max = 0;
    for (int i = 1; i < MAXLEN; i++) {
        if (count[i] > max)
            max = count[i];
    }

    printf("\nVertical Histogram:\n\n");
    for (int row = max; row > 0; row--) {
        for (int col = 1; col < MAXLEN; col++) {
            if (count[col] >= row)
                printf(" * ");
            else
                printf("   ");
        }
        putchar('\n');
    }

    for (int i = 1; i < MAXLEN; i++)
        printf("%2d ", i);
    putchar('\n');

    return 0;
}

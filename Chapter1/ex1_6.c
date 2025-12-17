/*Verify that the expression getchar() != EOF is 0 or 1.*/
#include <stdio.h>

int main() {
    int value;
    value = getchar() != EOF;
    printf("%d\n", value);
    return 0;
}

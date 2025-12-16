#include <stdio.h>

int main() {
    int value;
    value = getchar() != EOF;
    printf("%d\n", value);
    return 0;
}

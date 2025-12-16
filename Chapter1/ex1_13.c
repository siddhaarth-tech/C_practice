#include <stdio.h>

int main() {
    int ch, length = 0;
    int count[20] = {0};

    while ((ch = getchar()) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            if (length > 0 && length < 20)
                count[length]++;
            length = 0;
        } else {
            length++;
        }
    }

    for (int i = 1; i < 20; i++) {
        printf("%2d: ", i);
        for (int j = 0; j < count[i]; j++)
            putchar('*');
        putchar('\n');
    }
    return 0;
}

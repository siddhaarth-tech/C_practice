#include <stdio.h>

int main() {
    int ch;
    int freq[128] = {0};

    while ((ch = getchar()) != EOF)
        if (ch < 128)
            freq[ch]++;

    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("%c: ", i);
            for (int j = 0; j < freq[i]; j++)
                putchar('*');
            putchar('\n');
        }
    }
    return 0;
}

/*Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.*/

#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]) {
    int i, j, c;
    i = j = 0;

    while ((c = s1[i++]) != '\0') {
        /* Check for a-z pattern */
        if (s1[i] == '-' && s1[i + 1] >= c) {
            i++;  /* skip the dash */
            while (c < s1[i]) {
                s2[j++] = c++;
            }
        } else {
            s2[j++] = c;
        }
    }
    s2[j] = '\0';
}

int main() {
    char input[200];
    char result[1000];

    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);

    expand(input, result);

    printf("Expanded output: %s\n", result);

    return 0;
}

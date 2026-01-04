/*Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters.*/
#include <stdio.h>

void escape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++) {
        
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                printf("-t-");
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                printf("%c",t[i]);
                s[j++] = t[i];
                break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[]) {
    int i, j;
    for (i = j = 0; t[i] != '\0'; i++) {
        if (t[i] == '\\') {
            switch (t[++i]) {
                case 'n':
                    s[j++] = '\n';
                    break;
                case 't':
                    s[j++] = '\t';
                    break;
                default:
                    s[j++] = '\\';
                    s[j++] = t[i];
                    break;
            }
        } else {
            s[j++] = t[i];
        }
    }
    s[j] = '\0';
}
int getline_cus(char s[], int lim) {
    int c, i = 0, len = 0;

    while ((c = getchar()) != EOF) {
        len++;
        if (i < lim - 1) {
            s[i++] = c; 
        }
    }
    s[i] = '\0';
    return len; 
}

int main() {
    char input[100], escaped[200], unescaped[100];

    //printf("Enter a string (use real tab/newline):\n");
    getline_cus(input,100);

    escape(escaped, input);
    printf("\nEscaped string:\n%s\n", escaped);

    unescape(unescaped, escaped);
    printf("\nUnescaped string:\n%s\n", unescaped);

    return 0;
}


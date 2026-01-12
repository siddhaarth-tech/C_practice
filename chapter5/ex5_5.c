/*Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.*/

#include <stdio.h>

void my_strncpy(char *s, char *t, int n);
void my_strncat(char *s, char *t, int n);
int  my_strncmp(char *s, char *t, int n);

void remove_newline(char *s)
{
    while (*s) {
        if (*s == '\n') {
            *s = '\0';
            return;
        }
        s++;
    }
}

int main(void)
{
    char s[100];
    char t[100];
    int n;

    printf("string copy...\n");
    printf("enter the string t for strncpy: ");
    fgets(t, sizeof(t), stdin);
    remove_newline(t);

    printf("enter the value of n: ");
    scanf("%d", &n);
    getchar();   // clear newline

    my_strncpy(s, t, n);
    printf("the string s after string copy: %s\n\n", s);

    /* ---------- STRING CONCAT ---------- */
    char str1[100];
    char str2[100];

    printf("string concatenation...\n");
    printf("enter the string str1 for concat: ");
    fgets(str1, sizeof(str1), stdin);
    remove_newline(str1);

    printf("enter the string str2 for concat: ");
    fgets(str2, sizeof(str2), stdin);
    remove_newline(str2);

    printf("enter the number n: ");
    scanf("%d", &n);
    getchar();

    my_strncat(str1, str2, n);
    printf("the string after concatenation: %s\n\n", str1);

    /* ---------- STRING COMPARE ---------- */
    printf("string compare...\n");
    printf("enter the string s for compare: ");
    fgets(s, sizeof(s), stdin);
    remove_newline(s);

    printf("enter the string t for compare: ");
    fgets(t, sizeof(t), stdin);
    remove_newline(t);

    printf("enter the number n: ");
    scanf("%d", &n);

    int val = my_strncmp(s, t, n);

    if (val == 0)
        printf("both strings are equal\n");
    else if (val < 0)
        printf("string s is smaller\n");
    else
        printf("string t is smaller\n");

    return 0;
}

/* copy at most n characters */
void my_strncpy(char *s, char *t, int n)
{
    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}

/* concatenate at most n characters */
void my_strncat(char *s, char *t, int n)
{
    while (*s != '\0')
        s++;

    while (n > 0 && *t != '\0') {
        *s++ = *t++;
        n--;
    }
    *s = '\0';
}

/* compare at most n characters */
int my_strncmp(char *s, char *t, int n)
{
    while (n > 0 && *s && *t && (*s == *t)) {
        s++;
        t++;
        n--;
    }

    if (n == 0)
        return 0;

    return *s - *t;
}

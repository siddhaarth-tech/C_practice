/*Write a function reverse(s) that reverses the character string s. Use it to
write a program that reverses its input a line at a time.*/
#include <stdio.h>
#define MAXLINE 1000
int getline_cus(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

int main() {
    char line[MAXLINE];
    char copied[MAXLINE];
    int len;

    while ((len = getline_cus(line, MAXLINE)) > 0) {
        copy(copied, line);
        reverse(copied);
        printf("%s", copied);
    }

    return 0;
}

int getline_cus(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    if (c == '\n') {
        s[i] = c;
        i++;
    }

    s[i] = '\0';
    return i;
}
void copy(char to[], char from[]) {
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        i++;
}
void reverse(char s[]) {
    int i = 0, j;
    char temp;

    for (j = 0; s[j] != '\0'; j++)
        ;
    j--; 
    if (s[j] == '\n')
        j--;

    while (i < j) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

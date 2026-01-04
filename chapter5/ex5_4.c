/*Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.*/

#include <stdio.h>

int strend(char *s, char *t);

int main(void)
{
    char s[100];
    char t[100];

    printf("enter the string s : ");
    scanf("%s", s);

    printf("enter the string t : ");
    scanf("%s", t);

    if (strend(s, t))
        printf("the string s has t at the end\n");
    else
        printf("the string s does not have t at the end\n");

    return 0;
}

int strend(char *s, char *t)
{
    char *send = s;
    char *tend = t;

    /* move send to end of s */
    while (*send != '\0')
        send++;

    /* move tend to end of t */
    while (*tend != '\0')
        tend++;

    /* compare characters from the end */
    while (tend > t) {
        send--;
        tend--;
        if (*send != *tend)
            return 0;
    }

    return 1;
}

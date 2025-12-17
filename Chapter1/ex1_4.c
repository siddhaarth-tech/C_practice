/*Write a program to print the corresponding Celsius to Fahrenheit table.*/
#include <stdio.h>

int main() {
    int celsius;
    printf("Celsius  Fahrenheit\n");
    for (celsius = 0; celsius <= 100; celsius += 10)
        printf("%7d %11.1f\n", celsius, (celsius * 9.0/5.0) + 32);
    return 0;
}

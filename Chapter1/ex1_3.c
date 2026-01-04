#include <stdio.h>

int main() {
    int fahr;
    printf("Fahrenheit  Celsius\n");
    for (fahr = 0; fahr <= 300; fahr += 20)
        printf("%10d %8.1f\n", fahr, (5.0/9.0)*(fahr-32));
    return 0;
}

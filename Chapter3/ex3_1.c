/*
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

low = 0;
high = n - 1;
while (low <= high) {
mid = (low+high)/2;
if (x < v[mid])
high = mid + 1;
else if (x > v[mid])
low = mid + 1;
else
return mid;
}
return -1;
}
Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and
measure the difference in run-time.*/

#include <stdio.h>
int binsearch(int x, int v[], int n)
{
    int low = 0, high = n - 1, mid;
    /* Only one comparison inside the loop */
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return (x == v[low]) ? low : -1;
}
int main()
{
    int n, target;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter element to search: ");
    scanf("%d", &target);
    int result = binsearch(target, arr, n);
    if (result != -1)
        printf("Element %d found at index: %d\n", target, result);
    else
        printf("Element %d not found.\n", target);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main()
{
    // declaration
    int *min, *max, n, *arr;

    // get array size
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

    // reallocate the array to have size n
    arr = (int*)malloc(n * sizeof(int));

    // fill the array
    printf("Enter the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // declare min and max to be the first element of the array
    min = &arr[0];
    max = &arr[0];

    // find the min and max
    for (int i = 1; i < n; i++) {
        if (*(arr + i) > *max) {
            max = &arr[i];
        }
        if (*(arr + i) < *min) {
            min = &arr[i];
        }
    }

    // print the results
    printf("Maximum value: %d\n", *max);
    printf("Minimum value: %d\n", *min);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // declaration
    int n, *arr;

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

    // print the array in reverse
    printf("Reversed array: ");
    for (int i = n-1; i >= 0; i--) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    return 0;
}
#include <stdio.h>

void sort(int arr[], int n) {
    int temp; // temporary variable
    for (int i = 0; i < n -1; i++) { // iterate thru the entire array
        for (int j = 0; j< n - 1 -i; j++ ) { // iterate thru part of the array
            if (arr[j] > arr[j+1]) { // check if the next int is < then the next
                // swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    // declaration 
    int n;

    // get array size
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    //declaratin of array with size n
    int arr[n];

    // fill the array
    printf("Enter the array: \n");
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }

    // sort the array
    sort(arr, n);

    // print out the sorted array
    printf("Array in ascending order: \n");
    for (int i = 0; i < n; i++) {
        printf("%i\n", arr[i]);
    }
    printf("\n");
    
    return 0;
}
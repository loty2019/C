#include <stdio.h>

int main() {
    // declaration
    int n;

    // get the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    //declaratin of array with size n
    int arr[n];

    // fill the array
    printf("Elements of the array: \n");
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }
    
    // print the array starting from the end
    printf("Reversed array: \n");
    for (int i = n-1; i >= 0; i--) {
        printf("%i\n", arr[i]);
    }
    
    return 0;
}
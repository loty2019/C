#include <stdio.h>

double average(int arr[], int n) {
    // declaration
    double avg, sum = 0;

    // sum all the elements of the array together
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }

    // calculate the average
    avg = sum / n;
    return avg;
}


int main() {
    // declaration
    int n;

    // get the size of the arrray
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    //declaratin of array with size n
    int arr[n];

    // fill the array
    printf("Elements of the array: \n");
    for (int i = 0; i < n; i++) {
        scanf("%i", &arr[i]);
    }

    // print out the mean
    printf("The average value is: %.1f\n", average(arr, n));
    
    return 0;
}
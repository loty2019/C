#include <stdio.h>

int main() {
    // initialize variables
    int n;  
    int factorial = 1; 

    // get input, keep asking until its correct
    printf("Enter an Integer: ");
    scanf("%d", &n);
    while (n < 0 || n > 12) { // 12! is the higest storabe in an int
        printf("Error ---> has to be positive and <= 12\n");
        printf("Enter an Integer: ");
        scanf("%d", &n);
    }

    // calculate the factorial of n
    for (int i = 2; i <= n; i++) {
        factorial *= i;
    }

    // print the factorial 
    printf("The factorial of %d is %d\n", n, factorial);
    return 0;
}
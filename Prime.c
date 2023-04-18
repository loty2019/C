#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main() {
    // initalize variables
    int n;
    bool isPrime = true;

    // get input
    printf("Enter an Integer: ");
    scanf("%d", &n);

    // calcutlate if prime or not
    if (n <= 1) { 
        isPrime = false; // its prime if n<=1
    } else {
        for (int i = 2; i <= sqrt(n); i++) { // using sqrt of n makes th program faster
            if (n % i == 0) {
                isPrime = false;
                break; // if it not prime bake the loop
            }
        }
    }
    // print if its prime or not
    if (isPrime) {
        printf("Prime\n");
    } else {
        printf("Not Prime\n");
    }
    return 0;
}
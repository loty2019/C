#include <stdio.h>
#include <stdbool.h>

int main() {
    // initialize variables and constants
    const double pi = 3.14159;
    double r;

    // get input and keep asking if wrong
    printf("Enter the radius: ");
    scanf("%lf", &r);
    while (r < 0){
        printf("Error ---> has to be > 0\n");
        printf("Enter the radius: ");
        scanf("%lf", &r);
    }
    
    // print and calualate area and circumference
    printf("The area is %.3f\n", (pi * r * r));
    printf("The circumference is %.3f\n", (2 * pi * r));
    return 0;
}


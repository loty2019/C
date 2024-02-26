#include <stdio.h>

int main()
{
    // declaration
    int input;

    // get input 
    scanf("%i", &input);
    
    // check if input is >, <, =, 0
    if (input == 0) {
        printf("0 is neither positive nor negative\n");
    } else if (input > 0) {
        printf("%i is a positive number\n", input);
    } else {
        printf("%i is a negative number\n", input);
    }
    
    return 0;
}
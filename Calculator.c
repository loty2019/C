#include <stdio.h>

int main() {
    // initalize variables
    int x, y;
    char op;

    // get input
    tryAgain:
        printf("Enter an expression: ");
        scanf("%d%c%d", &x, &op, &y);

    // differnt cases for evey operation
    switch (op) {
        case '+':
            printf("Result: %d\n", (x + y));
            break;
        case '-':
            printf("Result: %d\n", (x - y));
            break;
        case '*':
            printf("Result: %d\n", (x * y));
            break;
        case '/':
            printf("Result: %.2f\n", (double)x / y);
            break;
        case '%':
            printf("Result: %d\n", (x % y));
            break;
        default:
            printf("Invalid operation\n");
            goto tryAgain; // if the operation is not valid
                           // ask for the input again
    }
    return 0;
}
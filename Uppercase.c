/*
    Lorenzo Orio
    April 18, 2023
    Approach:
        1. function to convert a string to uppercase
        2. check if string is empty
        3. print uppercase character
        4. call function recursively
        5. create main function
        6. declare variables
        7. get string
        8. print uppercase string
    Problems
     none
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// function to convert a string to uppercase
void Upper(char *str, int index)
{
    // check if string is empty
    if (index == strlen(str)) {
        return;
    }

    // print uppercase character
    printf("%c", toupper(str[index]));

    // call function recursively
    Upper(str, index + 1);
}

int main() {
    // declare variables
    char str[100];

    // get string
    printf("Enter string: ");
    scanf("%s", str);

    // print uppercase string
    printf("Output string: ");
    Upper(str, 0);
    printf("\n");
}
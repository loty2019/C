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
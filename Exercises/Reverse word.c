#include <stdio.h>
#include <string.h>

// function to reverse a string
void reverse(char *str, int len)
{
    // check if string is empty
    if (len == 0) {
        return;
    }

    // print character at index len - 1
    printf("%c", str[len - 1]);

    // call function recursively
    reverse(str, len - 1);
}

int main() {
    // declare variables
    char str[100];

    // get words
    printf("Enter a sentence: ");
    scanf("%[^\n]s", str);

    // print reverse string by calling the reverse function
    printf("Reverse Output: ");
    reverse(str, strlen(str));
    printf("\n");
}
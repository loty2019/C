#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // declaration
    char *str1;
    char *str2;

    // set array size to 100
    str1 = (char*)malloc(100 * sizeof(char));
    str2 = (char*)malloc(100 * sizeof(char));

    // get strings
    printf("Enter the first string: ");
    scanf("%s", str1);   
    printf("Enter the second string: ");
    scanf("%s", str2);

    // print concatenated string
    printf("Concatenated string: %s\n", strcat(str1, str2));

    return 0;
}
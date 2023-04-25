#include <stdio.h>

// define struct
struct student {
    char name[100];
    int marks[5];
    int total;
    char grade;
};

int main() {
    // declare variables
    struct student std;

    // get name
    printf("Name: ");
    scanf("%s", std.name);

    // get marks
    for (int i = 0; i < 5; i++) {
        printf("Enter marks for subject %d (out of 100): ", i + 1);
        scanf("%d", &std.marks[i]);
    }

    // calculate total
    std.total = 0;
    for (int i = 0; i < 5; i++) {
        std.total += std.marks[i];
    }

    // calculate grade
    if (std.total >= 450) {
        std.grade = 'A';
    } else if (std.total >= 400) {
        std.grade = 'B';
    } else if (std.total >= 350) {
        std.grade = 'C';
    } else if (std.total >= 300) {
        std.grade = 'D';
    } else {
        std.grade = 'F';
    }

    // print results
    printf("Hello %s, Your total marks are %d and Grade %c\n", std.name, std.total, std.grade);
}
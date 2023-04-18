/*
    Lorenzo Orio
    April 18, 2023
    Approach:
        1. define struct
        2. declare variables
        3. get number of doctors
        4. get doctors data
        5. get number of queries
        6. get queries
        7. loop through doctors
        8. compare query to the doctor's specialization
        9. print result
    Problems
     none
*/

#include <stdio.h>
#include <string.h>

// define struct
struct doc {
    char name[100];
    char spec[100];
};

int main() {
    // declare variables
    int n, q;
    char query[100];
    struct doc doctors[100];

    // get number of doctors
    printf("Enter the number of doctors: ");
    scanf("%d", &n);

    // get doctors data
    printf("Enter the name and specialization of the doctors: ");
    for (int i = 0; i < n; i++) {
        scanf("%s %s", doctors[i].name, doctors[i].spec);
    }
    
    // get number of queries
    printf("Enter the number of queries: ");
    scanf("%d", &q);

    // get queries
    for (int i = 0; i < q; i++) {
        printf("Enter the query (%d): ", i + 1);
        scanf("%s", query);
        // loop through doctors
        for (int j = 0; j < n; j++) {
            // compare query to the doctor's specialization
            if (strcmp(query, doctors[j].spec) == 0) {
                printf("Result (%d): %s \n", i + 1, doctors[j].name);
            }
        }
    }
}
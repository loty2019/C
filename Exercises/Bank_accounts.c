/*
    Lorenzo Orio
    April 27, 2023
    Approach:
        Struct:
            1. Create a struct account
                a. id
                b. name
                c. balance
            2. Create an array of struct accounts
        Partition:
            1. Set pivot as the last element
            2. Set i as the index of the smaller element
            3. For j = low to high - 1
                a. If element at j is less than pivot
                    i. Increment i
                    ii. Swap accounts[i] and accounts[j]
            4. Swap accounts[i + 1] and accounts[high]
            5. Return i + 1
        QuickSort:
            1. If low is less than high
                a. pi is partitioning index
                b. Sort elements before partition and after partition
        Main:
            1. Declare variables
            2. Open file
            3. Read the header row
            4. While the file is not empty
                a. Calculate total balance and total accounts
                b. Increment i
            5. Print total balance and total accounts
            6. Sort the accounts by balance
            7. Print the top 5 accounts
            8. Close file
    Problems
     none
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

// define struct account
struct account {
    int id;
    char name[100];
    double balance;
};

int partition(struct account accounts[], int low, int high) {
    // set pivot as the last element
    int pivot = accounts[high].balance;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (accounts[j].balance > pivot) {
            i++;

            // swap accounts[i] and accounts[j]
            struct account temp = accounts[i];
            accounts[i] = accounts[j];
            accounts[j] = temp;
        }
    }

    // swap accounts[i + 1] and accounts[high]
    struct account temp = accounts[i + 1];
    accounts[i + 1] = accounts[high];
    accounts[high] = temp;

    return (i + 1);
}

void quickSort(struct account accounts[], int low, int high) {
    // if low is less than high
    if (low < high) {
        // pi is partitioning index
        int pi = partition(accounts, low, high);

        // sort elements before partition and after partition
        quickSort(accounts, low, pi - 1);
        quickSort(accounts, pi + 1, high);
    }
}

int main() {
    // declare variables
    struct account accounts[1000];
    FILE *csvfile;
    int i = 0;
    double totalBalance = 0;
    int totalAccounts = 0;

    // open file
    csvfile = fopen("accounts.csv", "r");
    if (csvfile == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    // read the header row
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, csvfile);

    // while the file is not empty
    while (fscanf(csvfile, "%d,%[^,],$%lf", &accounts[i].id, accounts[i].name, &accounts[i].balance) != EOF) {
        // calculate total balance and total accounts
        totalBalance += accounts[i].balance;
        totalAccounts++;
        i++;
    }

    // print total balance and total accounts
    printf("Total accounts: %d\n", totalAccounts);
    printf("Total balance: $%.2lf\n", totalBalance);

    // sort the accounts by balance
    int n = sizeof(accounts) / sizeof(accounts[0]);
    quickSort(accounts, 0, n - 1);

    // print the top 5 accounts
    printf("\nTop 5 accounts:\n");
    for (int j = 0; j < 5; j++) {
        printf("%s: $%.2lf\n",accounts[j].name, accounts[j].balance);
    }

    // close file
    fclose(csvfile);
}


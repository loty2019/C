/*
Lorenzo Orio
    April 27, 2023
    Approach:
        Import:
            1. Open the CSV file
            2. Ask the user for the name of the CSV file
            3. check if the file exists
            4. Skip the first line
            5. Read the file line by line
            6. Write the data to the binary file
            7. Close the CSV file
        Export:
            1. Create a new CSV file
            2. Open the binary file
            3. Read the binary file line by line
            4. Write the data to the CSV file
            5. Close the CSV file
        Delete:
            1. Open the binary file
            2. Ask the user for the name of the contact to delete
            3. Check if the contact exists
            4. Delete the contact
            5. Close the binary file
    Problems
     none
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_SIZE 1024

struct phonebook
{
    char name[50];
    char number[15];
};

FILE *phonebook_file()
{
    FILE *fptr;
    if ((fptr = fopen("phonebook.bin", "ab+")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    return fptr;
}

void add_contact(FILE *fptr)
{
    struct phonebook contact;
    printf("Enter name: ");
    while (getchar() != '\n')
        ;
    scanf(" %[^\n]", contact.name);
    printf("Enter number: ");
    scanf("%s", contact.number);
    fwrite(&contact, sizeof(struct phonebook), 1, fptr);
    printf("Contact added successfully\n");
}

void search_contact(FILE *fptr)
{
    struct phonebook contact;
    char name[20];
    printf("Enter name: ");
    while (getchar() != '\n')
        ;
    scanf(" %[^\n]", name);
    rewind(fptr);
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
    {
        if (strcmp(contact.name, name) == 0)
        {
            printf("Number: %s\n", contact.number);
            return;
        }
    }
    printf("Contact not found.\n");
}

void list_contacts(FILE *fptr)
{
    struct phonebook contact;
    rewind(fptr);
    printf("Lisiting contacts:\n");
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
    {
        printf("Name: %s \t Number: %s\n", contact.name, contact.number);
    }
}

void delete_contact(FILE *fptr)
{
    struct phonebook contact;
    char name[20];
    printf("Enter name: ");
    while (getchar() != '\n');
    scanf(" %[^\n]", name);
    rewind(fptr);
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
    {
        if (strcmp(contact.name, name) == 0)
        {
            rewind(fptr);
            // delete the contact
            FILE *tempfile;
            if ((tempfile = fopen("temp.bin", "wb")) == NULL)
            {
                printf("Error! opening file");
                // Program exits if the file pointer returns NULL.
                exit(1);
            }
            
            // copy all contacts except the one to be deleted to the tempfile
            while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
            {
                if (strcmp(contact.name, name) != 0)
                {
                    fwrite(&contact, sizeof(struct phonebook), 1, tempfile);
                }
            }

            // make the tempfile the new phonebook file
            remove("phonebook.bin");
            fclose(fptr);
            fclose(tempfile);
            rename("temp.bin", "phonebook.bin");
            tempfile = phonebook_file();
            printf("Contact deleted successfully\n");
            return;
        }
    }
    printf("Contact not found\n");
}

void import_csv(FILE *fptr)
{
    char filename[20];
    struct phonebook contact;

    // get filename from user
    printf("Enter the name of the CSV file: ");
    scanf("%s", filename);

    // open the file
    FILE *csvfile = fopen(filename, "r");

    // check if file exists
    if (csvfile == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    // skip the first line
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, csvfile);
    rewind(fptr);

    printf("Importing from CSV...\n");
    while (getchar() != '\n')
        ;
    // read the file
    while (fscanf(csvfile, "\n%[^,],%[^\n]", contact.name, contact.number) != EOF)
    {
        fwrite(&contact, sizeof(struct phonebook), 1, fptr);
    }

    printf("Imported successfully\n");

    // close the file
    fclose(csvfile);
}

void export_csv(FILE *fptr)
{
    // create a new csv file
    FILE *newcsvfile;
    if ((newcsvfile = fopen("Export_Phonebook.csv", "w")) == NULL)
    {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    struct phonebook contact;
    rewind(fptr);
    printf("Exporting to CSV...\n");

    // add headers
    fprintf(newcsvfile, "Name,Phone Number\n");

    // read the file and write to csv
    while (fread(&contact, sizeof(struct phonebook), 1, fptr) == 1)
    {
        fprintf(newcsvfile, "%s,%s\n", contact.name, contact.number);
    }

    printf("Exported successfully\n");

    // close the file
    fclose(newcsvfile);
}

int main()
{
    // open the phonebook file
    FILE *fptr = phonebook_file();

    while (1)
    {
        int choice;
        printf("\n---------MENU---------\n");
        printf("1. Add contact\n");
        printf("2. Delete Contact\n");
        printf("3. Search contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Import from CSV\n");
        printf("6. Export from CSV\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        printf("----------------------\n\n");
        switch (choice)
        {
        case 1:
            add_contact(fptr);
            break;
        case 2:
            delete_contact(fptr);
            break;
        case 3:
            search_contact(fptr);
            break;
        case 4:
            list_contacts(fptr);
            break;
        case 5:
            import_csv(fptr);
            break;
        case 6:
            export_csv(fptr);
            break;
        case 7:
            fclose(fptr);
            return 0;
        default:
            printf("Invalid choice.\n");
            break;
        }
    }

    return 0;
}
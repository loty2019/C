#include <stdio.h>
#include <stdbool.h>

int main() {
    // initalize variables
    char name[50];
    int bYear, bMonth, bDay, cYear, cMonth, cDay, tYear, tMonth, tDay ;
    
    // assign values assuming its February 15 2023
    cYear = 2023;
    cMonth = 2;
    cDay = 15;
    tYear = 0;
    tMonth = 0;
    tDay = 0;

    // get inputs name and date of birth
    printf("Name: ");
    scanf("%s", name);
    printf("Date of Birth (YYYY/MM/DD): ");
    scanf("%d/%d/%d", &bYear, &bMonth, &bDay);

    // calculate how much time has passed
    tYear = cYear - bYear - 1; 
    tMonth = 12 - bMonth + cMonth; 
    // count days that have passed
    if (cDay >= bDay) {
        tMonth += 1; 
        tDay = cDay - bDay;
    } else {
        tDay = 30 + cDay - bDay;
    } 
    // adjust previous calculation
    tYear += tMonth / 12;
    tMonth = tMonth % 12;
    if (bDay > cDay) {
        tMonth -= 1;
        if (tMonth < 0) {
            tMonth += 12;
            tYear -= 1;
        }
    }
    // accpount for leap year and changing month                                                                                                                                                                                                                                                                                                                                                            
    int daysInMonth = 31;
    if (bMonth == 2) {
        daysInMonth = (bYear % 4 == 0) ? 29 : 28;
    } else if (bMonth == 4 || bMonth == 6 || bMonth == 9 || bMonth == 11) {
        daysInMonth = 30;
    }
    if (bDay > cDay) {
        tDay = daysInMonth - bDay + cDay;
    }
    // print output
    printf("Hello, %s! You are %d years, %d months and %d days old.\n", name, tYear, tMonth, tDay);
    return 0;
}
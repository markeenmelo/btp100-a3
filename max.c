#include <stdio.h>
#include <string.h>

// Max: clears extra characters after using scanf
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Max: makes a string lowercase WITHOUT using tolower()
// Max: we only convert A–Z by adding 32 (ASCII rule)
void makeLowercase(char *s) {
    int i = 0;
    while (s[i] != '\0') {                   // Max: loop through each character
        if (s[i] >= 'A' && s[i] <= 'Z') {    // Max: check if it's an uppercase letter
            s[i] = s[i] + 32;                // Max: convert to lowercase
        }
        i++;
    }
}

void trimNewline(char *s) { // Max: removes newline from fgets
    int len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {     // Max: check if last char is newline
        s[len - 1] = '\0';                   // Max: remove it
    }
}

// ======================================================
// OPTION 2 — Search Calls to Action by Category (BEGINNER)
// ======================================================
void searchCallsByCategory(const char *filename) {

    FILE *fp = fopen(filename, "r");      // Max: open the file

    if (fp == NULL) {                     // Max: check if file opened properly
        printf("Error opening file.\n");
        return;
    }

    char userCategory[64];                // Max: store user category
    char userLower[64];                   // Max: lowercase version for comparison

    printf("Enter category to search: ");
    fgets(userCategory, sizeof(userCategory), stdin); // Max: get full line input
    trimNewline(userCategory);                        // Max: remove newline

    strcpy(userLower, userCategory);      // Max: make a copy of user input
    makeLowercase(userLower);             // Max: convert it to lowercase

    char line[512];                       // Max: reads each line from file
    int found = 0;                        // Max: keeps track if a match is found

    printf("\n--- Results ---\n");

    while (fgets(line, sizeof(line), fp) != NULL) {  // Max: read file line by line

        char temp[512];
        strcpy(temp, line);               // Max: copy because strtok changes it

        // Max: split the line into parts
        char *number = strtok(temp, "|");        // part 1: call number
        char *category = strtok(NULL, "|");      // part 2: category
        char *description = strtok(NULL, "\n");  // part 3: description

        if (number == NULL || category == NULL || description == NULL) {
            continue;                    // Max: skip bad lines
        }

        char categoryLower[128];  // Max: make a lowercase copy of the category in the file
        strcpy(categoryLower, category);
        makeLowercase(categoryLower);     // Max: manually convert a-z

        // Max: check if they match
        if (strcmp(categoryLower, userLower) == 0) {
            found = 1;

            printf("Call #%s\n", number);
            printf("Category: %s\n", category);
            printf("Description: %s\n", description);
            printf("--------------------------------\n");
        }
    }

    if (!found) {  // Max: if nothing matched
        printf("No calls found in category '%s'.\n", userCategory);
    }

    fclose(fp);  // Max: close the file
}

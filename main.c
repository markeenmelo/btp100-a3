#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 10 // declares the max amount of items in the struct array

struct FileStruct { // struct for content analysis
	int number; // number variable for the record number
	char category[20]; // to store the category string
	char description[300]; // to store the contents of calls to action
};

void displayAll(struct FileStruct list[], int fileContentSize); // TYLER: prototype for display all function
void searchByCategory(struct FileStruct list[], int fileContentSize); // MAX: prototype for search by category function
void saveCategoryToFile(struct FileStruct list[], int fileContentSize); // MARCOS MELO: prototype for save category to file function

// helper functions
int loadFileContent(struct FileStruct fileContent[], int maxItems); // TYLER:
int caseInsensitiveStringsCompare(char str1[], char str2[]); // MARCOS MELO: prototype to compare two strings case-insensitive
void trimWhitespace(char str[]); // MARCOS MELO: prototype to trim leading/trailing whitespace
int extractUniqueCategories(struct FileStruct list[], int fileContentSize, char uniqueCategories[][20]); // MARCOS MELO: prototype to extract unique categories
void buildFilename(char filename[], char category[]); // MARCOS MELO: prototype to build filename from category

int main() { // begins the program
	struct FileStruct fileContent[MAX_ITEMS]; // creates a struct array of data type FileStruct and has max items as the size

	int fileContentSize = loadFileContent(fileContent, MAX_ITEMS);

	if (fileContentSize > 0) {
		int choice; // choice variable for switch
		do { // do while loop to keep the program going until the user enters 5 to exit
			printf("\n--- Truth and Reconciliation Calls to Action Menu ---\n");
			printf("1. Display all Calls to Action\n");
			printf("2. Search Calls to Action by category\n");
			printf("3. Display total number of Calls to Action\n");
			printf("4. Save Calls to Action by category to a new file\n");
			printf("5. Exit\n");
			printf("Enter your choice (1-5): ");
			scanf("%d", &choice); // scans the users choice
			switch (choice) { // switch cases for users selection
			case 1:
				displayAll(fileContent, fileContentSize); // calls the display all function and gives the function list and count value for running
				break;  // breaks the switch case when code above completes
			case 2:
				searchByCategory(fileContent, fileContentSize);
				break;
			case 3:
				printf("\nTotal number of Calls to Action: %d\n", fileContentSize); // prints the total calls to action
				break; // breaks the switch case when code above completes
			case 4:
				saveCategoryToFile(fileContent, fileContentSize); // calls the save category to file function
				break;
			case 5:
				printf("\nThank you for using the Truth and Reconciliation Calls to Action program!\n"); // case for when the user wants to exit
				break; // breaks the switch case when code above completes
			default:
				printf("\nInvalid choice. Please enter a number between 1 and 5.\n"); // default choice for when the user enters an invalid choice
			}
		} while (choice != 5); // condition of do/while loop to know when to stop the loop and exit
	}

	return 0; // returns 0 to say the program executed successfully
}

// TYLER: Displays all calls to action in a table format.
void displayAll(struct FileStruct list[], int fileContentSize) { // display all function that returns void, takes a struct of datatype fileContent and count for running
	// Print header
	printf("\nAll Calls to Action:\n");
	printf("| %-6s | %-15s | %s\n", "Number", "Category", "Description");
	printf("+--------+-----------------+--------------------------------+\n");
	for (int i = 0; i < fileContentSize; i++) { // for loop that prints all the record's numbers and calls to actions
		printf("| %-6d | %-15s | %s\n", list[i].number, list[i].category, list[i].description); // prints the record number, category, and full description
	}
	printf("\n");
}

// Max: Search and display all calls to action that match category in table format.
void searchByCategory(struct FileStruct list[], int fileContentSize) {
	char searchCategory[50]; // character array to store category user searches for
	int count = 0; // variable to count matching calls to action

	// ask user to type category they want to search for
	printf("\nEnter category to search (e.g., Child Welfare, Education, Health, Justice): ");
	scanf(" %[^\n]", searchCategory);
	printf("\n");

	// create header
	printf("Calls to Action in category '%s':\n", searchCategory);
	printf("| %-6s | %-15s | %s\n", "Number", "Category", "Description");
	printf("+--------+-----------------+--------------------------------+\n");

	// compare category from list with user search
	for (int i = 0; i < fileContentSize; i++) {
		// use helper function to compare strings (case-insensitive)
		if (caseInsensitiveStringsCompare(list[i].category, searchCategory) == 0) {
			// if find match, increase counter
			count++;

			// display the matching call to action in table row
			printf("| %-6d | %-15s | %s\n", list[i].number, list[i].category, list[i].description);
		}
	}

	// after checking all records, if 0 match, tell the user
	if (count == 0) {
		printf("No Calls to Action found in category '%s'.\n", searchCategory);
	} else {
		// if we found matches, tell user how many
		printf("\nTotal found: %d\n", count);
	}
}

// MARCOS MELO: function to save Calls to Action by category to a new file.
void saveCategoryToFile(struct FileStruct list[], int fileContentSize) {
	char uniqueCategories[MAX_ITEMS][20]; // array to store unique categories
	int uniqueCount = 0; // counter for unique categories
	int categoryChoice; // variable for user's category selection
	char filename[50]; // variable to store the output filename
	int found = 0; // counter for matching records found

	// extract unique categories from the list using helper function
	uniqueCount = extractUniqueCategories(list, fileContentSize, uniqueCategories);

	// display category menu to user
	printf("\nAvailable Categories:\n");
	for (int i = 0; i < uniqueCount; i++) {
		printf("%d. %s\n", i + 1, uniqueCategories[i]); // display each category with number
	}

	printf("Enter the number of the category to save: "); // prompt user for selection
	scanf("%d", &categoryChoice); // read user's choice

	// validate user input and process if valid
	if (categoryChoice >= 1 && categoryChoice <= uniqueCount) {
		// build filename using helper function
		buildFilename(filename, uniqueCategories[categoryChoice - 1]);

		FILE* fp = fopen(filename, "w"); // open file for writing

		if (fp == NULL) {
			printf("Error: Could not create file '%s'.\n", filename);
		} else {
			// loop through all records to find matching category
			for (int n = 0; n < fileContentSize; n++) {
				if (caseInsensitiveStringsCompare(list[n].category, uniqueCategories[categoryChoice - 1]) == 0) { // use helper function to compare (case-insensitive)
					fprintf(fp, "%s\n", list[n].description); // write matching record to file
					found++; // increment counter for each match
				}
			}

			fclose(fp); // close the file after writing

			printf("\n%d Calls to Action saved to '%s' successfully.\n", found, filename); // confirm successful save
		}
	} else {
		printf("\nInvalid category selection. Please choose a number from the list.\n"); // error message for invalid choice
	}
}

int loadFileContent(struct FileStruct fileContent[], int maxItems) {
	int i = 0;
	int count = 0;
	FILE* fp = fopen("calls_to_action.txt", "r");
	if (fp == NULL) {
		printf("Error: Unable to open 'calls_to_action.txt'. Please ensure the file exists in the current directory.\n");
		return 0; // return 0 if file not found
	}
	while (i < maxItems && fscanf(fp, "%d|%19[^|]|%299[^\n]%*c", &fileContent[i].number, fileContent[i].category, fileContent[i].description) == 3) {
		trimWhitespace(fileContent[i].category); // trim whitespace from category
		trimWhitespace(fileContent[i].description); // trim whitespace from description
		i++;
		count++;
	}
	fclose(fp);
	return count;
}



// MARCOS MELO: Function to compare two strings case-insensitive, returns 0 if equal.
int caseInsensitiveStringsCompare(char str1[], char str2[]) {
	int i = 0; // index for character comparison
	
	// compare strings character by character (case-insensitive)
	while (str1[i] != '\0' || str2[i] != '\0') {
		char c1 = str1[i];
		char c2 = str2[i];
		
		// convert both to lowercase for comparison
		if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
		if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;
		
		if (c1 != c2) return 1; // strings don't match
		i++; // move to next character
	}
	
	return 0; // return 0 if match, 1 if different
}

// MARCOS MELO: Function to trim leading and trailing whitespace from string.
void trimWhitespace(char str[]) {
	int i = 0;
	int start = 0;
	int end = 0;
	
	// find first non-whitespace character
	while (str[i] == ' ' || str[i] == '\n') {
		i++;
	}
	start = i;
	
	// find last non-whitespace character
	i = 0;
	while (str[i] != '\0') {
		if (str[i] != ' ' && str[i] != '\n') {
			end = i;
		}
		i++;
	}
	
	// move trimmed part to beginning of string
	for (i = 0; start <= end; i++, start++) {
		str[i] = str[start];
	}
	
	str[i] = '\0'; // add null terminator
}

// MARCOS MELO: Function to extract unique categories from the list.
int extractUniqueCategories(struct FileStruct list[], int fileContentSize, char uniqueCategories[][20]) {
	int uniqueCount = 0; // counter for unique categories
	
	// loop through all records to find unique categories
	for (int i = 0; i < fileContentSize; i++) {
		int isDuplicate = 0; // flag to check if category already exists
		
		// check if category already in unique list (case-insensitive)
		for (int j = 0; j < uniqueCount; j++) {
			if (caseInsensitiveStringsCompare(list[i].category, uniqueCategories[j]) == 0) isDuplicate = 1; // category already exists
		}
		
		// if not duplicate, add to unique categories
		if (isDuplicate == 0) {
			strcpy(uniqueCategories[uniqueCount], list[i].category); // copy category to unique list
			uniqueCount++; // increment unique category counter
		}
	}
	
	return uniqueCount; // return the number of unique categories found
}

// MARCOS MELO: Function to build filename from category name.
void buildFilename(char filename[], char category[]) {
	int i = 0; // index for processing characters
	
	// copy and convert category to lowercase for filename
	while (category[i] != '\0') {
		filename[i] = category[i]; // copy character
		// convert uppercase to lowercase
		if (filename[i] >= 'A' && filename[i] <= 'Z') filename[i] = filename[i] + 32; // convert to lowercase
		// replace spaces with underscores
		if (filename[i] == ' ') filename[i] = '_'; // replace space with underscore
		i++; // move to next character
	}
	
	// append "_calls.txt"
	char suffix[] = "_calls.txt";
	int j = 0; // index for suffix
	
	while (suffix[j] != '\0') {
		filename[i] = suffix[j]; // copy suffix character
		i++; // move to next position
		j++; // move to next suffix character
	}
	
	filename[i] = '\0'; // add null terminator
}

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
void saveCategoryToFile(struct FileStruct list[], int fileContentSize); // MARCOS MELO: prototype for save category to file function

// helper functions
void loadFileContent(struct FileStruct fileContent[], int maxItems);
int compareStrings(char str1[], char str2[]); // MARCOS MELO: prototype to compare two strings
void copyString(char dest[], char src[]); // MARCOS MELO: prototype to copy string from src to dest
int extractUniqueCategories(struct FileStruct list[], int fileContentSize, char uniqueCategories[][20]); // MARCOS MELO: prototype to extract unique categories
void buildFilename(char filename[], char category[]); // MARCOS MELO: prototype to build filename from category

int main() { // begins the program
	struct FileStruct fileContent[MAX_ITEMS]; // creates a struct array of data type FileStruct and has max items as the size
	int choice; // choice variable for switch

	loadFileContent(fileContent, MAX_ITEMS);
	const int fileContentSize = sizeof(fileContent)/sizeof(fileContent[0]); // variable for counting the calls to action

	do { // do while loop to keep the program going until the user enters 5 to exit
		printf("1. Display all Calls to Action\n");
		printf("2. Search for all Calls to Action\n");
		printf("3. Display total number of Calls to Action\n");
		printf("4. Save Calls to Action by category to a new file\n");
		printf("5. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice); // scans the users choice  
		switch (choice) { // switch cases for users selection 
		case 1:
			displayAll(fileContent, fileContentSize); // calls the display all function and gives the function list and count value for running
			break;  // breaks the switch case when code above completes
		case 2:
			break;
		case 3:
			printf("Total Calls to Action: %d\n", fileContentSize); // prints the total calls to action
			break; // breaks the switch case when code above completes
		case 4:
			saveCategoryToFile(fileContent, fileContentSize); // calls the save category to file function
			break;
		case 5:
			printf("Thank you for using our program\n\n"); // case for when the user wants to exit
			break; // breaks the switch case when code above completes
		default:
			printf("Invalid choice, please try again\n"); // default choice for when the user enters an invalid choice
		}
	} while (choice != 5); // condition of do/while loop to know when to stop the loop and exit 

	return 0; // returns 0 to say the program executed successfully
}

// Marcos Melo. Displays all calls to action in a spreadsheet format.
void displayAll(struct FileStruct list[], int fileContentSize) { // display all function that returns void, takes a struct of datatype fileContent and count for running
	// Print header
	printf("| %-6s | %-15s | %-60s |\n", "Number", "Category", "Description");
	printf("+--------+-----------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
	for (int i = 0; i < fileContentSize; i++) { // for loop that prints all the record's numbers and calls to actions
		printf("| %-6d | %-15s | %-60s |\n", list[i].number, list[i].category, list[i].description); // prints the record number, category, and description in columns
	}
}

void loadFileContent(struct FileStruct fileContent[], int maxItems) {
	int local_count = 0;
	FILE* fp = fopen("calls_to_action.txt", "r");
	if (fp == NULL) printf("Error opening file.\n");
	while (local_count < maxItems && fscanf(fp, "%d|%19[^|]|%299[^\n]%*c", &fileContent[local_count].number, fileContent[local_count].category, fileContent[local_count].description) == 3) {
		local_count++;
	}
	fclose(fp);
}

// MARCOS MELO: Function to compare two strings manually, returns 1 if equal, 0 if different.
int compareStrings(char str1[], char str2[]) {
	int i = 0; // index for character comparison
	int match = 1; // assume strings match initially
	
	// compare strings character by character
	while (str1[i] != '\0' || str2[i] != '\0') {
		if (str1[i] != str2[i]) match = 0; // strings don't match
		i++; // move to next character
	}
	
	return match; // return 1 if match, 0 if different
}

// MARCOS MELO: Function to copy string from src to dest manually.
void copyString(char dest[], char src[]) {
	int i = 0; // index for copying characters
	
	// copy each character from source to destination
	while (src[i] != '\0') {
		dest[i] = src[i]; // copy character
		i++; // move to next character
	}
	dest[i] = '\0'; // add null terminator
}

// MARCOS MELO: Function to extract unique categories from the list.
int extractUniqueCategories(struct FileStruct list[], int fileContentSize, char uniqueCategories[][20]) {
	int uniqueCount = 0; // counter for unique categories
	
	// loop through all records to find unique categories
	for (int i = 0; i < fileContentSize; i++) {
		int isDuplicate = 0; // flag to check if category already exists
		
		// check if category already in unique list
		for (int j = 0; j < uniqueCount; j++) {
			if (compareStrings(list[i].category, uniqueCategories[j]) == 1) isDuplicate = 1; // category already exists
		}
		
		// if not duplicate, add to unique categories
		if (isDuplicate == 0) {
			copyString(uniqueCategories[uniqueCount], list[i].category); // copy category to unique list
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

// MARCOS MELO: Function to save Calls to Action by category to a new file.
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
	
	printf("Enter category number to save: "); // prompt user for selection
	scanf("%d", &categoryChoice); // read user's choice
	
	// validate user input and process if valid
	if (categoryChoice >= 1 && categoryChoice <= uniqueCount) {
		// build filename using helper function
		buildFilename(filename, uniqueCategories[categoryChoice - 1]);
		
		FILE* fp = fopen(filename, "w"); // open file for writing
		
		if (fp != NULL) { // check if file opened successfully
			// loop through all records to find matching category
			for (int n = 0; n < fileContentSize; n++) {
				if (compareStrings(list[n].category, uniqueCategories[categoryChoice - 1]) == 1) { // use helper function to compare
					fprintf(fp, "%s\n", list[n].description); // write matching record to file
					found++; // increment counter for each match
				}
			}
			
			fclose(fp); // close the file after writing
			
			printf("%d Calls to Action saved to %s\n", found, filename); // confirm successful save
		}

		if (fp == NULL) printf("Error creating file.\n"); // check if file opening failed
	} else {
		printf("Invalid category selection.\n"); // error message for invalid choice
	}
}

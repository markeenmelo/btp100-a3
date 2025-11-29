#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 10 // declares the max amount of items in the struct array

struct fileContents { // struct for content analysis
	int number; // number variable for the record number
	char category[20]; // to store the category string
	char description[300]; // to store the contents of calls to action
};

void displayAll(struct fileContents list[], int count); // TYLER: prototype for display all function
void saveCategoryToFile(struct fileContents list[], int count); // MARCOS MELO: prototype for save category to file function

// helper functions
int compareStrings(char str1[], char str2[]); // MARCOS MELO: prototype to compare two strings
void copyString(char dest[], char src[]); // MARCOS MELO: prototype to copy string from src to dest
int extractUniqueCategories(struct fileContents list[], int count, char uniqueCategories[][20]); // MARCOS MELO: prototype to extract unique categories
void buildFilename(char filename[], char category[]); // MARCOS MELO: prototype to build filename from category

int main() { // begins the program
	struct fileContents list[MAX_ITEMS]; // creates a struct array of data type fileContents and has max items as the size
	int count = 0; // variable for counting the calls to action
	int choice; // choice variable for switch

	FILE* fp = NULL; //  declares fp variable for file opening
	fp = fopen("calls_to_action.txt", "r"); // assigns fp to the contents of the calls to action file 

	if (fp == NULL) { // checks for file opening error (file not found, bad file name, permission error 
		printf("Error opening file.\n");
		return 1; // returns non zero value 
	}

	while (fscanf(fp, "%d|%19[^|]|%299[^\n]%*c", &list[count].number, list[count].category, list[count].description) == 3){ // counts the amount of calls to actions 
		count++; // increments by 1 for every sucessful read
	}

	fclose(fp); // closes the file after reading and analysing

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
			displayAll(list, count); // calls the display all function and gives the function list and count value for running
			break;  // breaks the switch case when code above completes
		case 2:
			break;
		case 3:
			printf("Total Calls to Action: %d\n", count); // prints the total calls to action
			break; // breaks the switch case when code above completes
		case 4:
			saveCategoryToFile(list, count); // calls the save category to file function
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

void displayAll(struct fileContents list[], int count) { // display all function that returns void, takes a struct of datatype fileContent and count for running
	for (int i = 0; i < count; i++) { // for loop that prints all the record's numbers and calls to actions
		printf("Record %d: %s\n\n", list[i].number,  list[i].description); // prints the record number and calls to action content
	}
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
int extractUniqueCategories(struct fileContents list[], int count, char uniqueCategories[][20]) {
	int uniqueCount = 0; // counter for unique categories
	
	// loop through all records to find unique categories
	for (int i = 0; i < count; i++) {
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
void saveCategoryToFile(struct fileContents list[], int count) {
	char uniqueCategories[MAX_ITEMS][20]; // array to store unique categories
	int uniqueCount = 0; // counter for unique categories
	int categoryChoice; // variable for user's category selection
	char filename[50]; // variable to store the output filename
	int found = 0; // counter for matching records found
	
	// extract unique categories from the list using helper function
	uniqueCount = extractUniqueCategories(list, count, uniqueCategories);
	
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
			for (int n = 0; n < count; n++) {
				if (compareStrings(list[n].category, uniqueCategories[categoryChoice - 1]) == 1) { // use helper function to compare
					fprintf(fp, "%d|%s|%s\n", list[n].number, list[n].category, list[n].description); // write matching record to file
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

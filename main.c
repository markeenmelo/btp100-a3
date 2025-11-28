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

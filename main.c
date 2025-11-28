#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 10

struct fileAnalysis {
	int* number;
	char* category[20];
	char description[300];
};

void displayAll(struct fileAnalysis list[], int count) {
	for (int i = 0; i < count; i++) {
		printf("Record %d: %s\n\n", list[i].number,  list[i].description);
	}
}

int main() {
	struct fileAnalysis list[MAX_ITEMS];
	int count = 0;
	int choice;

	FILE* fp = NULL;
	fp = fopen("calls_to_action.txt", "r");

	if (fp == NULL) {
		printf("Error opening file.\n");
		return 1;
	}

	while (fscanf(fp, "%d|%49[^|]|%399[^\n]%*c",&list[count].number, list[count].category, list[count].description) == 3){
		count++;
	}

	fclose(fp);

	do {
		printf("1. Display all Calls to Action\n");
		printf("3. Display total number of Calls to Action\n");
		printf("5. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			displayAll(list, count);
			break;
		case 3:
			printf("Total Calls to Action: %d\n", count);
			break;
		case 5:
			choice = 5;
			printf("bye");
		default:
			printf("Invalid choice, please try again\n");
		}
	} while (choice != 5);


	return 0;
}

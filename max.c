// Max: search and display all calls to action that match category
void searchByCategory() {
    // Max: Declare variable to hold the file pointer 
    FILE *file;
    
    // Max: Create character array to store each line we read from  file 
    char line[500];
    
    // Max: Create character array to store category user searches for
    char searchCategory[50];
    
    // Max: Create variable to count matching calls to action
    int count = 0;
    
    // Max: Open the file in read mode
    file = fopen("calls_to_action.txt", "r");
    
    // Max: Check if the file opened right, if not, show an error message 
    if (file == NULL) {
        printf("Error: Could not open the file!\n");
        return;
    }
    
    // Max: Ask user to type category they want to search for
    printf("Enter category to search (Child Welfare, Education, Health, Justice): ");
    
    // Max: Read category name from the user and store it in searchCategory
    scanf(" %[^\n]", searchCategory);
    printf("\n");
    
    // Max: Create header
    printf("Calls to Action in category '%s':\n", searchCategory);
    printf("===========================================\n");
    
    // Max: Loop through file and read one line at a time
    while (fgets(line, sizeof(line), file) != NULL) {
        // Max: Create variables to store the different parts of line
        char number[10];
        char category[50];
        char description[400];
        
        // Max: Use sscanf to split line into 3 parts separated by |
        sscanf(line, "%[^|]|%[^|]|%[^\n]", number, category, description);
        
     // Max: Compare  category from  file with user search
    while (fscanf(file, "%d|%[^|]|%[^\n]\n", &number, category, description) == 3) {
        // Max: strcmp returns 0 if the strings are exactly the same
        if (strcmp(category, searchCategory) == 0) {
            // Max: If find match, increase counter
            count++;

            // Max: Display the matching call to action
            printf("Call to Action #%d\n", number);
            printf("Category: %s\n", category);
            printf("Description: %s\n", description);
            printf("-------------------------------------------\n");
        }
    
    // Max: After checking all lines, if 0 match, tell the user
    if (count == 0) {
        printf("No Calls to Action found in category '%s'.\n", searchCategory);
    } else {
        // Max: If we found matches, tell user how
        printf("\nTotal found: %d\n", count);
    }
    
    // Max: Close the file
    fclose(file);
}

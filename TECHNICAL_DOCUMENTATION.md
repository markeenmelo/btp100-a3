# BTP100-A3: Truth and Reconciliation Calls to Action Analyzer

## Project Overview

This C program is a comprehensive data analysis tool designed to process and analyze Canada's Truth and Reconciliation Commission's Calls to Action. The project demonstrates fundamental C programming concepts including file I/O operations, string manipulation, data structures, and user interaction through a command-line interface.

### Educational Context

This is Assignment 3 for BTP100 — Introduction to Programming Using C at Seneca Polytechnic. The assignment combines technical programming skills with meaningful content about Indigenous communities and reconciliation in Canada.

## Project Collaborators

This project was developed collaboratively by a team of three students, each contributing to different aspects of the implementation:

- **Marcos Melo**: Led the development of string processing utilities, file export functionality, and helper functions including case-insensitive string comparison, whitespace trimming, unique category extraction, and dynamic filename generation.

- **Tyler**: Implemented the core display functionality and file loading system, including the main data structure design, file parsing logic, and comprehensive display formatting for all records.

- **Max**: Developed the search and filtering capabilities, focusing on category-based search functionality with case-insensitive matching and result formatting.

The collaborative approach allowed for modular development, with each team member taking ownership of specific components while ensuring integration and consistency across the codebase.

## Technical Architecture

### Data Structure Design

The program uses a structured approach to data management:

```c
struct FileStruct {
    int number;           // Call to Action number
    char category[20];    // Category name (Child Welfare, Education, etc.)
    char description[300]; // Full description text
};
```

**Key Design Decisions:**
- Fixed-size arrays for memory management in introductory C programming
- String buffers sized to accommodate typical content lengths
- Structured data organization for efficient processing

### Core Components

#### 1. File Loading System

**Function:** `loadFileContent()`  
**Developer:** Tyler

```c
int loadFileContent(struct FileStruct fileContent[], int maxItems) {
    int i = 0;
    int count = 0;
    FILE* fp = fopen("calls_to_action.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open 'calls_to_action.txt'. Please ensure the file exists in the current directory.\n");
        return 0;
    }
    while (i < maxItems && fscanf(fp, "%d|%19[^|]|%299[^\n]%*c", &fileContent[i].number, fileContent[i].category, fileContent[i].description) == 3) {
        trimWhitespace(fileContent[i].category);
        trimWhitespace(fileContent[i].description);
        i++;
        count++;
    }
    fclose(fp);
    return count;
}
```

**Technical Implementation:**
- Uses `fscanf()` with format string parsing for structured data extraction
- Format `"%d|%19[^|]|%299[^\n]%*c"` handles pipe-delimited data
- Buffer overflow protection with width specifiers
- Automatic whitespace trimming for data consistency
- Returns count of successfully loaded records

#### 2. String Processing Utilities

**Case-Insensitive String Comparison:**  
**Developer:** Marcos Melo

```c
int caseInsensitiveStringsCompare(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' || str2[i] != '\0') {
        char c1 = str1[i];
        char c2 = str2[i];
        
        // Convert to lowercase for comparison
        if (c1 >= 'A' && c1 <= 'Z') c1 = c1 + 32;
        if (c2 >= 'A' && c2 <= 'Z') c2 = c2 + 32;
        
        if (c1 != c2) return 1;
        i++;
    }
    return 0;
}
```

**Whitespace Trimming:**  
**Developer:** Marcos Melo

```c
void trimWhitespace(char str[]) {
    int i = 0;
    int start = 0;
    int end = 0;
    
    // Find first non-whitespace character
    while (str[i] == ' ' || str[i] == '\n') {
        i++;
    }
    start = i;
    
    // Find last non-whitespace character
    i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ' && str[i] != '\n') {
            end = i;
        }
        i++;
    }
    
    // Move trimmed part to beginning
    for (i = 0; start <= end; i++, start++) {
        str[i] = str[start];
    }
    
    str[i] = '\0';
}
```

#### 3. Data Analysis Functions

**Display All Records:**  
**Developer:** Tyler

```c
void displayAll(struct FileStruct list[], int fileContentSize) {
    printf("\nAll Calls to Action:\n");
    printf("| %-6s | %-15s | %s\n", "Number", "Category", "Description");
    printf("+--------+-----------------+--------------------------------+\n");
    for (int i = 0; i < fileContentSize; i++) {
        printf("| %-6d | %-15s | %s\n", list[i].number, list[i].category, list[i].description);
    }
    printf("\n");
}
```

**Category-Based Search:**  
**Developer:** Max

```c
void searchByCategory(struct FileStruct list[], int fileContentSize) {
    char searchCategory[50];
    int count = 0;

    printf("\nEnter category to search (e.g., Child Welfare, Education, Health, Justice): ");
    scanf(" %[^\n]", searchCategory);
    
    printf("Calls to Action in category '%s':\n", searchCategory);
    printf("| %-6s | %-15s | %s\n", "Number", "Category", "Description");
    printf("+--------+-----------------+--------------------------------+\n");

    for (int i = 0; i < fileContentSize; i++) {
        if (caseInsensitiveStringsCompare(list[i].category, searchCategory) == 0) {
            count++;
            printf("| %-6d | %-15s | %s\n", list[i].number, list[i].category, list[i].description);
        }
    }

    if (count == 0) {
        printf("No Calls to Action found in category '%s'.\n", searchCategory);
    } else {
        printf("\nTotal found: %d\n", count);
    }
}
```

#### 4. File Export System

**Unique Category Extraction:**  
**Developer:** Marcos Melo

```c
int extractUniqueCategories(struct FileStruct list[], int fileContentSize, char uniqueCategories[][20]) {
    int uniqueCount = 0;
    
    for (int i = 0; i < fileContentSize; i++) {
        int isDuplicate = 0;
        
        // Check if category already exists (case-insensitive)
        for (int j = 0; j < uniqueCount; j++) {
            if (caseInsensitiveStringsCompare(list[i].category, uniqueCategories[j]) == 0) {
                isDuplicate = 1;
            }
        }
        
        if (isDuplicate == 0) {
            strcpy(uniqueCategories[uniqueCount], list[i].category);
            uniqueCount++;
        }
    }
    
    return uniqueCount;
}
```

**Dynamic Filename Generation:**  
**Developer:** Marcos Melo

```c
void buildFilename(char filename[], char category[]) {
    int i = 0;
    
    // Convert category to lowercase and replace spaces with underscores
    while (category[i] != '\0') {
        filename[i] = category[i];
        if (filename[i] >= 'A' && filename[i] <= 'Z') filename[i] = filename[i] + 32;
        if (filename[i] == ' ') filename[i] = '_';
        i++;
    }
    
    // Append "_calls.txt"
    char suffix[] = "_calls.txt";
    int j = 0;
    while (suffix[j] != '\0') {
        filename[i] = suffix[j];
        i++;
        j++;
    }
    
    filename[i] = '\0';
}
```

## Installation and Usage

### Prerequisites

- C compiler GCC
- `calls_to_action.txt` data file in project directory

### Compilation

```bash
gcc main.c -o main
```

### Running the Program

```bash
./main
```

### User Interface

The program presents an interactive menu:

```
--- Truth and Reconciliation Calls to Action Menu ---
1. Display all Calls to Action
2. Search Calls to Action by category
3. Display total number of Calls to Action
4. Save Calls to Action by category to a new file
5. Exit
Enter your choice (1-5):
```

## Data Format

### Input File Structure

The `calls_to_action.txt` file follows a pipe-delimited format:

```
number|category|description
```

**Example:**
```
1|Child Welfare|We call upon the federal, provincial, territorial, and Aboriginal governments to reduce the number of Aboriginal children in care...
2|Education|We call upon the federal government to enact an Aboriginal Languages Act...
```

### Supported Categories

- Child Welfare
- Education
- Health
- Justice

## Error Handling

The program implements comprehensive error handling:

1. **File Access Errors**: Graceful handling of missing or unreadable data files
2. **Input Validation**: Menu choice validation and category search validation
3. **Memory Safety**: Buffer overflow protection in string operations
4. **Case-Insensitive Operations**: Robust string matching regardless of input case

## Performance Considerations

### Memory Management

- Fixed-size arrays limit scalability but ensure predictable memory usage
- Maximum of 10 records defined by `MAX_ITEMS` constant
- String buffers sized to prevent overflow while accommodating typical content

### Algorithmic Efficiency

- Linear search algorithms (O(n)) for category matching
- Unique category extraction uses nested loops (O(n²))
- File I/O operations minimized through batch processing

## Educational Value

### Programming Concepts Demonstrated

1. **Structures and Data Organization**: Complex data management using structs
2. **File I/O Operations**: Reading and writing text files with formatted parsing
3. **String Manipulation**: Case-insensitive comparison, trimming, and transformation
4. **Menu-Driven Interfaces**: User interaction design and input validation
5. **Modular Programming**: Function decomposition and helper utilities
6. **Error Handling**: Robust error checking and user feedback

### Cross-Curricular Integration

The assignment combines technical programming skills with:
- Indigenous Studies content
- Social justice awareness
- Canadian history and reconciliation
- Professional ethics and cultural sensitivity

## Future Enhancements

### Potential Improvements

1. **Dynamic Memory Allocation**: Replace fixed arrays with malloc/free for scalability
2. **Database Integration**: SQLite backend for larger datasets
3. **Data Visualization**: Charts and graphs for category distribution

### Scalability Considerations

- Current implementation suitable for educational purposes and small datasets
- Production use would require dynamic memory management
- Large-scale deployment would benefit from database integration

## Development Team

### Core Contributors

- **Marcos Melo**: String processing, file export, and utility functions
- **Tyler**: File loading system and display functionality  
- **Max**: Search and filtering capabilities

### Development Approach

The team employed a collaborative development model with clear separation of concerns:

1. **Modular Design**: Each developer focused on specific functional modules
2. **Code Integration**: Regular integration sessions to ensure compatibility
3. **Peer Review**: Cross-review of code for consistency and quality
4. **Documentation**: Comprehensive inline comments and function documentation

## Contributing

This project is designed as an educational assignment. Modifications should maintain:
- Code clarity and readability
- Consistent commenting style
- Adherence to C11 standards
- Educational value for introductory programming students
- Respect for the collaborative development approach established by the original team

## License

This project is intended for educational use within the BTP100 course framework.

---

*Technical Documentation Generated: December 2025*
*Course: BTP100 — Introduction to Programming Using C*
*Institution: Seneca Polytechnic*
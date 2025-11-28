# BTP 100 — Introduction to Programming Using C

## Assignment 3 (10%)

Title: Data Analysis with Text Files — Exploring Truth and Reconciliation in Canada

---

## Learning Outcomes

By completing this assignment, you will:

- Develop proficiency in file handling in C.
- Gain practice in string manipulation and data processing.
- Engage with meaningful content about Indigenous communities and the path to reconciliation.

---

## Assignment Description

Write a C program that reads, processes, and analyzes information from a text file containing data about Canada's Truth and Reconciliation Calls to Action. The program should demonstrate file input/output operations, loops, arrays, and string manipulation in C. This assignment also encourages reflection on the impact of reconciliation initiatives.

## Dataset

A sample text file (`calls_to_action.txt`) is provided. Each line in the file represents one of the Truth and Reconciliation Commission's Calls to Action (https://www.rcaanc-cirnac.gc.ca/eng/1524494530110/1557511412801).

File format (each line):

1|Category|Description

Example lines:

```
1|Child Welfare|We call upon the federal, provincial, territorial, and Aboriginal governments to reduce the number of Aboriginal children in care...
2|Education|We call upon the federal government to provide adequate funding for First Nations students...
3|Justice|We call upon all levels of government to fully adopt and implement the United Nations Declaration on the Rights of Indigenous Peoples as the framework for reconciliation...
```

Each line contains:

- The Call to Action number
- The Category
- The Description

---

## Tasks

### 1. Program Features

Write a C program that:

- Opens the provided `calls_to_action.txt` file for reading.
- Reads the data line by line and processes it.
- Presents a user menu to interact with the data.

Menu (display to user):

```
1. Display all Calls to Action
2. Search Calls to Action by category
3. Display total number of Calls to Action
4. Save Calls to Action by category to a new file
5. Exit
```

### 2. Functional Requirements

- Option 1: Display all Calls to Action neatly formatted.
- Option 2: Prompt the user to enter a category (e.g., "Education") and display all matching Calls to Action (case-insensitive).
- Option 3: Count and display the total number of Calls to Action in the file.
- Option 4: Prompt the user for a category, create a new text file (e.g., `education_calls.txt`), and write all matching Calls to Action to the file.
- Option 5: Exit the program.

### 3. Error Handling

- Handle cases where the file cannot be opened (for example, file not found).
- Validate user input and ensure category searches are case-insensitive.

### 4. Reflection

Include a brief paragraph as a separate document reflecting on how understanding the Truth and Reconciliation Calls to Action enhances your knowledge of Indigenous issues in Canada.

---

## Submission Requirements

- Submit your source code (`.c` files).
- Include a brief reflective document (`.md` or `.txt`).
- Ensure your program is well-commented and follows coding best practices.

---

## Evaluation Criteria

| Criteria                                      | Marks |
|----------------------------------------------|:-----:|
| Correct file reading and processing          | 20    |
| Menu functionality                           | 30    |
| Error handling                               | 10    |
| Code structure and readability               | 10    |
| Reflection on the assignment                 | 10    |
| Overall program correctness and thinking     | 20    |

Total: 100

---

## Provided Files

- `calls_to_action.txt` — sample dataset used by the program.

---

## Notes

- Keep category matching case-insensitive and trim whitespace when parsing.
- Write clear prompts and error messages for users.
- You may assume lines follow the `number|category|description` format.
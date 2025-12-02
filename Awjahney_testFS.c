#include "Awjahney_libFS.h"
#include <ctype.h>  // For tolower()


// Function to display the menu
void displayMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Create a file\n");
    printf("2. Open a file\n");
    printf("3. Write to a file\n");
    // Added the missing options in the menu: Read, Close, and Delete file.
    printf("4. Read from a file\n"); // This is to read the file contents.
    printf("5. Close a file\n"); // This is to close the currently open the file.
    printf("6. Delete a file\n"); // This is to delete a file.
    printf("7. Exit\n");
    printf("Enter your choice: ");
}

// Function to wait for user input to continue
void waitForUser() {
    printf("\nPress Enter to continue...");
    getchar();  // Wait for Enter key
}

int main() {
    char filename[MAX_FILENAME];
    char introduction[] = "Hello, my name is Awjahney!\n\n"
                        "This is my Project 4 for CS 470 - Operating Systems course.\n"
                        "This project involves creating a file system library in C.\n"
                        "I hope you find my implementation useful and straightforward to use!";
    int file_index = -1;  // Track the currently open file
    int choice;
    char buffer[MAX_FILE_SIZE];

    while (1) {
        displayMenu();
        scanf("%d", &choice);  // Get user choice
        getchar();  // Clear the newline character from the buffer

        switch (choice) {
            case 1:  // Create a file
                printf("Enter the filename to create: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileCreate(filename) != 0) {
                    printf("Error creating file.\n");
                }
                waitForUser();
                break;

            case 2:  // Open a file
                printf("Enter the filename to open: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                file_index = fileOpen(filename);
                if (file_index == -1) {
                    printf("Error opening file.\n");
                }
                waitForUser();
                break;

            case 3:  // Write to a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Writing introduction to file '%s'...\n", filename);
                    if (fileWrite(file_index, introduction) != 0) {
                        printf("Error writing to file.\n");
                    }
                }
                waitForUser();
                break;

            // Added a menu option where the user can select option 4 to read from an already open file.
            // The fileRead function is called to read the contents of the open file and print them to the screen.
            case 4:  // Read from a file
                if (file_index == -1) {
                    printf("Error: No file is open. Please open a file first.\n");
                } else {
                    printf("Reading from file '%s'...\n", filename);
                    if (fileRead(file_index, buffer, MAX_FILE_SIZE) == 0) {
                        printf("File Contents:\n%s\n", buffer); // Print the contents read from the file
                    } else {
                        printf("Error reading from file.\n");
                    }
                }
                waitForUser();
                break;
            
            // Added a menu option where the user can select option 5 to close the currently open file.

            case 5:  // Close a file
                if (file_index == -1) {
                    printf("Error: No file is open.\n");
                } else {
                    fileClose(file_index);
                }
                waitForUser();
                break;
            
            // Added a menu option where the user can select option 6 to delete a file.
            // The fileDelete function is called to delete the specified file from the disk.
            case 6:  // Delete a file
                printf("Enter the filename to delete: ");
                fgets(filename, MAX_FILENAME, stdin);
                filename[strcspn(filename, "\n")] = '\0';  // Remove newline
                if (fileDelete(filename) != 0) {
                    printf("Error deleting file.\n");
                }
                waitForUser();
                break;

            case 7:  // Exit
                printf("Exiting the program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                waitForUser();
                break;
        }
    }
    return 0;
}
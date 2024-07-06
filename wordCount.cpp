#include <stdio.h>
#include <ctype.h>

// Function Prototypes
void countFileContent(const char *filename, int *lines, int *words, int *characters);

int main() {
    char filename[100];
    int lines = 0, words = 0, characters = 0;
Prompt the user to enter the file name
    
    printf("Enter the filename: ");
    scanf("%99s", filename); // Limit the input to avoid overflow

    // Count the content of the file
    countFileContent(filename, &lines, &words, &characters);

    // Display the results
    printf("\nFile Analysis:\n");
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);

    return 0;
}

// Function to count lines, words, and characters in a file
void countFileContent(const char *filename, int *lines, int *words, int *characters) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s.\n", filename);
        return;
    }

    int ch;
    int inWord = 0;
    *lines = 0;
    *words = 0;
    *characters = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*characters)++;

        if (ch == '\n') {
            (*lines)++;
        }

        if (isspace(ch)) {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            (*words)++;
        }
    }

    // Check if the last character was not a newline and the file is not empty
    if (*characters > 0 && ch != '\n' && ch != EOF) {
        (*lines)++;
    }

    fclose(file);
}


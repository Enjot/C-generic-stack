#include "util.h"
#include "handler_error.h"


void util_clear_screen() {
	system("cls");
}

void util_press_any_key_to_continue() {
	printf("\nPress any key to continue... ");
	getch();
	printf("\n\n");
}

char* util_scan_user_input(FILE* file) {

    int chunk = 16;

    char* buffer = NULL;
    char* temp = NULL;

    size_t current_size = 0;
    int index = 0;
    int character = 0;

    while ((character = getc(file)) != '\n' && character != EOF && character != '\0') {
        if (current_size <= index) {
            current_size += chunk;
            temp = realloc(buffer, current_size);
            if (!temp) {
                free(buffer);
                buffer = NULL;
                error_memory_allocation("Couldn't reallocate for user input", "util_user_input()");
                return NULL;
            }
            buffer = temp;
        }

        buffer[index++] = (char)character;
    }

    temp = realloc(buffer, index + 1);
    if (!temp) {
        free(buffer);
        buffer = NULL;
        error_memory_allocation("Couldn't reallocate for user input", "util_user_input()");
        return NULL;
    }
    buffer = temp;
    buffer[index] = 0;

    return buffer;
}

char* read_line() {
    size_t capacity = 64;    // Starting buffer size
    size_t length = 0;       // Number of characters read
    char* buffer = malloc(capacity);
    if (!buffer) {
        return NULL; // Allocation failed
    }

    int c;
    // Read characters one by one from stdin
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        // Check if we need more space (+1 for the null terminator later)
        if (length + 1 >= capacity) {
            capacity *= 2; // Double the capacity
            char* temp = realloc(buffer, capacity);
            if (!temp) {
                free(buffer);
                return NULL; // Reallocation failed
            }
            buffer = temp;
        }
        buffer[length++] = (char)c;
    }

    // Null-terminate the string
    buffer[length] = '\0';

    // If the user pressed Ctrl+D (EOF) before typing anything, you might want to handle that case:
    // if (length == 0 && c == EOF) {
    //     free(buffer);
    //     return NULL;
    // }

    return buffer;
}
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

char* util_scan_user_input() {
    size_t capacity = 4;
    size_t length = 0;
    char* buffer = malloc(capacity);
    if (!buffer) {
        error_memory_allocation("Couldn't allocate memory for user input", "util_scan_user_input()");
        return NULL;
    }

    int c;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char* temp = realloc(buffer, capacity);
            if (!temp) {
                free(buffer);
                error_memory_allocation("Couldn't allocate memory for user input", "util_scan_user_input()");
                return NULL;
            }
            buffer = temp;
        }
        buffer[length++] = (char)c;
    }

    buffer[length] = '\0';

    return buffer;
}
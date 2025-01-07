#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "message.h"

void util_clear_screen() {
#ifdef _WIN32
    system("cls");
#elif defined(__linux__) || defined(__APPLE__)
    system("clear");
#else
    printf("\n\n");
#endif
}

void util_press_to_continue() {
#ifdef _WIN32
    system("pause");
#elif defined(__linux__) || defined(__APPLE__)
    printf("Press ENTER to continue...");
    fflush(stdout);
    getchar();  // Wait for user to press enter
#else
    printf("\n\n");
#endif
}

char *util_scan_user_input() {
    size_t capacity = 4;
    size_t length = 0;
    char *buffer = malloc(capacity);
    if (!buffer) {
        message_error(
            ERROR_MEMORY_ALLOCATION,
            "Couldn't allocate memory for user input",
            "util_scan_user_input()"
        );
        return NULL;
    }

    int c;

    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        if (length + 1 >= capacity) {
            capacity *= 2;
            char *temp = realloc(buffer, capacity);
            if (!temp) {
                free(buffer);
                message_error(
                    ERROR_MEMORY_ALLOCATION,
                    "Couldn't allocate memory for user input",
                    "util_scan_user_input()"
                );
                return NULL;
            }
            buffer = temp;
        }
        buffer[length++] = (char) c;
    }

    buffer[length] = '\0';

    return buffer;
}

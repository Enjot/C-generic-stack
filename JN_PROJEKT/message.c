#include <stdio.h>
#include "message.h"
#include "util.h"

static const char *error_type_formatted(const ERROR_TYPE error_type) {
    switch (error_type) {
        case ERROR_FILE_NOT_FOUND: return "\n* FILE NOT FOUND ERROR!\n";
        case ERROR_FILE_IS_EMPTY: return "\n* EMPTY FILE ERROR!\n";
        case ERROR_FILE_OPEN: return "\n* OPENING FILE ERROR!\n";
        case ERROR_FILE_READ: return "\n* READING FILE ERROR!\n";
        case ERROR_FILE_WRITE: return "\n* WRITING TO FILE ERROR!\n";
        case ERROR_NULL_POINTER: return "\n* NULL POINTER ERROR!\n";
        case ERROR_MEMORY_ALLOCATION: return "\n* MEMORY ALLOCATION ERROR!\n";
        case ERROR_INVALID_ARGUMENT: return "\n* INVALID ARGUMENT ERROR!\n";
        default: return "\n* UNKNOWN ERROR\n";
    }
}

void message_error(
    const ERROR_TYPE error_type,
    const char *message,
    const char *source
) {
    printf("%s", error_type_formatted(error_type));
    printf("Source: %s\n", source);
    printf("Message: %s\n", message);
    util_press_to_continue();
}

void message_debug(
    const char* message,
    const char* source
) {
    printf("Source: %s\n", source);
    printf("Message: %s\n", message);
    util_press_to_continue();
}

void message_info(const char *message) {
    printf("%s\n", message);
    util_press_to_continue();
}

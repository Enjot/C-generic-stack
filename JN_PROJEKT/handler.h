#pragma once
#include <stdbool.h>

typedef enum {
    ERROR_FILE_NOT_FOUND = 1,
    ERROR_FILE_IS_EMPTY = 2,
    ERROR_FILE_OPEN = 3,
    ERROR_FILE_READ = 4,
    ERROR_FILE_WRITE = 5,
    ERROR_NULL_POINTER = 6,
    ERROR_MEMORY_ALLOCATION = 7,
    ERROR_INVALID_ARGUMENT = 8
} ERROR_TYPE;

void handler_verify_for_fatal_errors();
bool handler_is_stack_empty();
bool handler_is_file();
bool handler_is_file_empty();
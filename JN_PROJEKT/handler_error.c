#include "handler_error.h"

void error_file_not_found(const char* message, const char* source) {
	printf("\n* OPENING FILE ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_open(const char* message, const char* source) {
	printf("\n* OPENING FILE ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_empty(const char* message, const char* source) {
	printf("\n* EMPTY FILE ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_read(const char* message, const char* source) {
	printf("\n* READING FILE ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_write(const char* message, const char* source) {
	printf("\n* WRITING TO FILE ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_null_pointer(const char* message, const char* source) {
	printf("\n* NULL POINTER ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_memory_allocation(const char* message, const char* source) {
	printf("\n* MEMORY ALLOCATION ERROR!\n");
	printf("Source: %s\n", source);
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}
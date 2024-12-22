#pragma once
#include "handler_error.h"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void error_file_open(char* message) {
	printf("\n* OPENING FILE ERROR!\n");
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_read(char* message) {
	printf("\n* READING FILE ERROR!\n");
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_file_write(char* message) {
	printf("\n* WRITING TO FILE ERROR!\n");
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_memory_not_allocated(char* message) {
	printf("\n* MEMORY NOT ALLOCATED ERROR!\n");
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}

void error_memory_allocation(char* message) {
	printf("\n* MEMORY ALLOCATION ERROR!\n");
	printf("Message: %s\n", message);
	util_press_any_key_to_continue();
}
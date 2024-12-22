#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_student.h"
#include "stack.h"

typedef enum MenuEvent {
	MAIN_MENU = 0,
	PRINT_STACK = 1,
	PRINT_TOP = 2,
	PRINT_AT_DEPTH = 3,
	PUSH_TO_STACK = 4,
	POP_FROM_STACK = 5,
	CLEAR_STACK = 6,
	SAVE_TO_DISK = 7,
	LOAD_FROM_DISK = 8,
	EXIT = 9
} MenuEvent;

void ui_run_menu();
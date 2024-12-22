#pragma once
#include "stack.h"
#include "my_student.h"

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

static void ui_print_stack(Stack* stack);
static void ui_print_top(Stack* stack);
static void ui_print_at_depth(Stack* stack);
static void ui_push_to_stack(Stack* stack);
static void ui_pop_from_stack(Stack* stack);
static void ui_clear_stack(Stack* stack);

static void ui_save_stack(Stack* stack);
static void ui_load_stack(Stack* stack);

static void ui_on_event(enum MenuEvent* event, unsigned short selected_event);
static void ui_print_menu();

static void my_exit(Stack* stack);
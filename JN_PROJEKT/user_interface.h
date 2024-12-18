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

void ui_print_stack(Stack stack);
void ui_print_top(Stack stack);
void ui_print_at_depth(Stack stack);
void ui_push_to_stack(Stack* stack);
void ui_pop_from_stack(Stack* stack);
void ui_clear_stack(Stack* stack);

void ui_save_stack(Stack* stack);
void ui_load_stack(Stack* stack);

void ui_on_event(enum MenuEvent* event, unsigned short selected_event);
void ui_print_menu();
void ui_clear();
void ui_press_any_key_to_continue();
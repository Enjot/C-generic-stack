#pragma once


enum MenuState {
	MAIN_MENU = 0,
	PRINT_STACK = 1,
	PRINT_TOP_FROM_STACK = 2,
	PRINT_FROM_STACK = 3,
	ADD_TO_STACK = 4,
	REMOVE_FROM_STACK = 5,
	EXIT = 6
};

void ui_run_menu();
void ui_print_stack();
void ui_print_top_from_stack();
void ui_print_from_stack(int index);
void ui_add_to_stack();
void ui_remove_from_stack();
void update_state(enum MenuState* state, unsigned short new_state);

void ui_print_menu();
void ui_clear();
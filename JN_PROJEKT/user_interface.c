#include <stdbool.h>
#include "user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "my_student.h">
#include <string.h>
#include "util.h"

void ui_run_menu() {

	Stack stack = stack_init();

	MenuEvent event = MAIN_MENU;

	while (event != EXIT) {
		ui_print_menu();
		unsigned short selected_state;
		scanf_s("%hu", &selected_state);
		ui_on_event(&event, selected_state);
		util_clear_screen();
		switch (event) {
		case MAIN_MENU:
			// option "0" - it's hidden
			break;
		case PRINT_STACK:
			ui_print_stack(stack);
			ui_on_event(&event, MAIN_MENU);
			break;
		case PRINT_TOP:
			ui_print_top(stack);
			break;
		case PRINT_AT_DEPTH:
			ui_print_at_depth(stack);
			break;
		case PUSH_TO_STACK:
			// TODO run corresponding function
			ui_push_to_stack(&stack);
			ui_on_event(&event, MAIN_MENU);
			break;
		case POP_FROM_STACK:
			ui_pop_from_stack(&stack);
			break;
		case CLEAR_STACK:
			ui_clear_stack(&stack);
			break;
		case SAVE_TO_DISK:
			ui_save_stack(&stack);
			break;
		case LOAD_FROM_DISK:
			ui_load_stack(&stack);
			break;
		case EXIT:
			// TODO run corresponding function
			break;
		default:
			break;
		}
	}
}

static void ui_print_stack(Stack stack) {
	if (stack.top == NULL) {
		printf("Stack is empty\n");
	}
	else {
		student_print_header();
		StackNode* current_node = stack.top;
		while (current_node != NULL) {
			MyStudent* student = (MyStudent*)current_node->item;
			student_print(student);
			current_node = current_node->next;
		}
	}

	util_press_any_key_to_continue();
}

static void ui_print_top(Stack stack) {
	if (stack.top == NULL) {
		printf("Stack is empty\n");
	}
	else {
		student_print_header();
		student_print(stack.top->item);
	}

	util_press_any_key_to_continue();
}

static void ui_print_at_depth(Stack stack) {
	int depth = 1;
	printf("Enter depth: ");
	scanf_s("%d", &depth);
	void* item = stack_get_at_depth(stack, depth);
	util_clear_screen();
	student_print_header();
	student_print(item);
	util_press_any_key_to_continue();
}

static void ui_push_to_stack(Stack* stack) {

	char surname[256];
	int birth_year;
	FieldOfStudy field_of_study;

	util_clear_screen();
	printf("ADDING STUDENT TO STACK\n");
	printf("Enter surname: ");
	scanf_s("%s", surname, 256);
	util_clear_screen();
	printf("Enter year of birth: ");
	scanf_s("%d", &birth_year);
	util_clear_screen();
	student_print_fields_of_study();
	printf("Choose field of study: ");
	scanf_s("%d", &field_of_study);

	MyStudent* student = student_create(surname, birth_year, field_of_study);

	stack_push(stack, student);
}

static void ui_pop_from_stack(Stack* stack) {\
	stack_pop(stack);
}

static void ui_clear_stack(Stack* stack) {
	stack_clear(stack);
}

static void ui_save_stack(Stack* stack) {
	stack_save_to_file(
		stack,
		"backup.bin",
		student_serialize
	);
}

static void ui_load_stack(Stack* stack) {
	stack_load_from_file(
		stack,
		"backup.bin",
		student_deserialize
	);
}

static void ui_on_event(
	enum MenuEvent* event,
	unsigned short selected_event
) {
	switch (selected_event) {
	case 0:
		*event = MAIN_MENU;
		break;
	case 1:
		*event = PRINT_STACK;
		break;
	case 2:
		*event = PRINT_TOP;
		break;
	case 3:
		*event = PRINT_AT_DEPTH;
		break;
	case 4:
		*event = PUSH_TO_STACK;
		break;
	case 5:
		*event = POP_FROM_STACK;
		break;
	case 6:
		*event = CLEAR_STACK;
		break;
	case 7:
		*event = SAVE_TO_DISK;
		break;
	case 8:
		*event = LOAD_FROM_DISK;
		break;
	case 9:
		*event = EXIT;
		break;
	default:
		// TODO some invalid input handling
		*event = MAIN_MENU;
	}
}

static void ui_print_menu() {
	util_clear_screen();
	printf("=========== STACK MANAGEMENT ===========\n");
	printf("========================================\n");
	printf("== 1. PRINT STACK                     ==\n");
	printf("== 2. PRINT TOP                       ==\n");
	printf("== 3. PRINT AT DEPTH                  ==\n");
	printf("==                                    ==\n");
	printf("== 4. PUSH TO STACK                   ==\n");
	printf("== 5. POP FROM STACK                  ==\n");
	printf("== 6. CLEAR STACK                     ==\n");
	printf("==                                    ==\n");
	printf("== 7. SAVE TO DISK                    ==\n");
	printf("== 8. LOAD FROM DISK                  ==\n");
	printf("==                                    ==\n");
	printf("== 9. EXIT                            ==\n");
	printf("========================================\n");
	printf("CHOOSE ACTION: ");
}
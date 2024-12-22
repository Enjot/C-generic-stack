#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_interface.h"
#include "stack.h"
#include "util.h"
#include "handler_error.h"
#include "handler_message.h"
#include "my_student.h"


static void ui_print_stack(Stack* stack) {
	if (!stack->top) {
		message_generic("Stack is empty");
		return;
	}

	student_print_header();
	StackNode* current = stack->top;
	while (current) {
		MyStudent* student = (MyStudent*)current->item;
		student_print(student);
		current = current->next;
	}

	util_press_any_key_to_continue();
}

static void ui_print_top(Stack* stack) {
	if (!stack) {
		error_memory_allocation("Stack is not initialized", "ui_print_top()");
		return;
	}
	if (stack->top == NULL) {
		message_generic("Stack is empty");
		return;
	}

	student_print_header();
	student_print(stack->top->item);

	util_press_any_key_to_continue();
}

static void ui_print_at_depth(Stack* stack) {
	if (!stack) {
		error_memory_allocation("Stack is not initialized", "ui_print_at_depth()");
		return;
	}
	if (stack->top == NULL) {
		message_generic("Stack is empty");
		return;
	}
	int depth = 1;
	printf("Enter depth (starting at 1): ");
	scanf_s("%d", &depth);
	while (getchar() != '\n') {};
	void* item = stack_get_at_depth(stack, depth);
	if (!item) {
		message_generic("Depth exceeds stack size");
		return;
	}
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

	while (getchar() != '\n') {};
	util_clear_screen();
	printf("Enter year of birth: ");
	scanf_s("%d", &birth_year);
	while (getchar() != '\n') {};
	util_clear_screen();
	student_print_fields_of_study();
	printf("Choose field of study: ");
	scanf_s("%d", &field_of_study);
	while (getchar() != '\n') {};
	MyStudent* student = student_create(surname, birth_year, field_of_study);
	if (!student) {
		message_generic("Failed to create student. Push operation aborted");
		return;
	}
	bool result = stack_push(stack, student);
	if (result) {
		message_generic("Student pushed to stack successfully");
	}
	else {
		message_generic("Failed to create student. Push operation aborted");
	}
}

static void ui_pop_from_stack(Stack* stack) {
	void* item = stack_pop(stack);
	if (!item) {
		message_generic("Stack is already empty. Nothing can be popped");
		return;
	}
	student_print_header();
	student_print(item);
	stack->destroy_item(item);
	message_generic("popped from stack successfully");
}

static void ui_clear_stack(Stack* stack) {
	if (!stack->top) {
		message_generic("Stack is empty already");
		return;
	}
	stack_clear(stack);
	message_generic("Stack cleared successfully");
}

static void ui_save_stack(Stack* stack) {
	stack_save_to_file(
		stack,
		"backup.bin",
		student_serialize
	);
	message_generic("Stack saved successfully");
}

static void ui_load_stack(Stack* stack) {
	bool result = stack_load_from_file(
		stack,
		"backup.bin",
		student_deserialize
	);
	if (result) {
		message_generic("Stack loaded successfully");
	}
	else {
		message_generic("Couldn't load students from file");
	}

}

static void ui_on_event(
	enum MenuEvent* event,
	unsigned short selected_event
) {
	switch (selected_event) {
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
		*event = FIND_ELEMENT;
		break;
	case 5:
		*event = PUSH_TO_STACK;
		break;
	case 6:
		*event = POP_FROM_STACK;
		break;
	case 7:
		*event = CLEAR_STACK;
		break;
	case 8:
		*event = SAVE_TO_DISK;
		break;
	case 9:
		*event = LOAD_FROM_DISK;
		break;
	case 0:
		*event = EXIT;
		break;
	case 99:
		*event = MAIN_MENU;
		break;
	default:
		message_generic("Invalid input. Return to main menu");
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
	printf("== 4. FIND ELEMENT                    ==\n");
	printf("==                                    ==\n");
	printf("== 5. PUSH TO STACK                   ==\n");
	printf("== 6. POP FROM STACK                  ==\n");
	printf("== 7. CLEAR STACK                     ==\n");
	printf("==                                    ==\n");
	printf("== 8. SAVE TO DISK                    ==\n");
	printf("== 9. LOAD FROM DISK                  ==\n");
	printf("==                                    ==\n");
	printf("== 0. EXIT                            ==\n");
	printf("========================================\n");
	printf("Choose action: ");
}

static bool compare_student_surname(void* item, void* criteria) {
	if (!item || !criteria) return false;
	MyStudent* student = (MyStudent*)item;
	char* target_surname = (char*)criteria;
	return strcmp(student->surname, target_surname) == 0;
}

static void ui_find_in_stack(Stack* stack) {
	char target_surname[256];
	printf("Enter surname to search: ");
	scanf_s("%s", target_surname, 256);
	while (getchar() != '\n') {};

	void* found_item = stack_find(stack, compare_student_surname, target_surname);
	if (found_item) {
		student_print_header();
		student_print((MyStudent*)found_item);
		util_press_any_key_to_continue();
	}
	else {
		message_generic("Student with the given surname not found.");
	}
}

static void my_exit(Stack* stack) {
	stack_destroy(stack);
	exit(EXIT_SUCCESS);
}

void ui_run_menu() {

	Stack* stack = stack_init(student_free);

	MenuEvent event = MAIN_MENU;

	while (event != EXIT) {
		ui_print_menu();
		unsigned short selected_state;
		scanf_s("%hu", &selected_state);
		while (getchar() != '\n') {};
		ui_on_event(&event, selected_state);
		util_clear_screen();
		switch (event) {
		case MAIN_MENU:
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
		case FIND_ELEMENT:
			ui_find_in_stack(stack);
			break;
		case PUSH_TO_STACK:
			ui_push_to_stack(stack);
			ui_on_event(&event, MAIN_MENU);
			break;
		case POP_FROM_STACK:
			ui_pop_from_stack(stack);
			break;
		case CLEAR_STACK:
			ui_clear_stack(stack);
			break;
		case SAVE_TO_DISK:
			ui_save_stack(stack);
			break;
		case LOAD_FROM_DISK:
			ui_load_stack(stack);
			break;
		case EXIT:
			my_exit(stack);
			break;
		default:
			break;
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include "user_interface.h"
#include "stack.h"
#include "util.h"
#include "message.h"
#include "my_student.h"

static void ui_print_stack() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	student_print_header();
	const STACK_NODE* current = stack->top;
	while (current) {
		const MY_STUDENT* student = current->item;
		student_print(student);
		current = current->next;
	}

	util_press_to_continue();
}

static void ui_print_top() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	student_print_header();
	student_print(stack->top->item);

	util_press_to_continue();
}

static void ui_print_at_depth() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	int depth = 1;
	printf("Enter depth (starting at 1): ");
	scanf_s("%d", &depth);
	while (getchar() != '\n') {
	};
	void* item = stack_get_at_depth(depth);
	if (!item) {
		message_info("Couldn't find any student at given depth");
		return;
	}
	util_clear_screen();
	student_print_header();
	student_print(item);
	util_press_to_continue();
}

static void ui_push_to_stack() {
	handler_verify_for_fatal_errors();

	util_clear_screen();
	printf("ADDING STUDENT TO STACK\n");
	printf("Enter surname: ");
	char* surname = util_scan_user_input();
	if (!surname) {
		message_info("Failed to add surname. Push operation aborted");
		return;
	}

	util_clear_screen();
	printf("Enter year of birth: ");
	int birth_year;
	scanf_s("%d", &birth_year);
	while (getchar() != '\n') {};

	util_clear_screen();
	student_print_fields_of_study();
	printf("Choose field of study: ");
	FIELD_OF_STUDY field_of_study;
	scanf_s("%d", &field_of_study);
	while (getchar() != '\n') {};

	MY_STUDENT* student = student_create(surname, birth_year, field_of_study);
	if (!student) {
		free(surname);
		message_info("Failed to create student. Push operation aborted");
		return;
	}

	const RESULT result = stack_push(student);

	if (result == SUCCESS) message_info("Student pushed to stack successfully");
	else message_info("Failed to create student. Push operation aborted");
}

static void ui_pop_from_stack() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	void* item = stack_pop();
	student_print_header();
	student_print(item);
	stack->destroy_item(item);
	message_info("popped from stack successfully");
}

static void ui_clear_stack() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	stack_clear(stack);
	message_info("Stack cleared successfully");
}

static void ui_save_stack() {
	const RESULT result = stack_save_to_file(student_serialize);
	if (result == SUCCESS) {
		message_info("Stack saved successfully");
	}
}

static void ui_load_stack() {
	const RESULT result = stack_load_from_file(student_deserialize);

	if (result == SUCCESS) message_info("Stack loaded successfully");
	else message_info("Couldn't load students from file");
}

static void ui_on_event(
	MENU_EVENT* event,
	const unsigned short selected_event
) {
	switch (selected_event) {
	case 1: *event = PRINT_STACK;
		break;
	case 2: *event = PRINT_TOP;
		break;
	case 3: *event = PRINT_AT_DEPTH;
		break;
	case 4: *event = FIND_ELEMENTS;
		break;
	case 5: *event = PUSH_TO_STACK;
		break;
	case 6: *event = POP_FROM_STACK;
		break;
	case 7: *event = CLEAR_STACK;
		break;
	case 8: *event = SAVE_TO_DISK;
		break;
	case 9: *event = LOAD_FROM_DISK;
		break;
	case 0: *event = EXIT;
		break;
	case 99: *event = MAIN_MENU;
		break;
	default:
		message_info("Invalid input. Return to main menu");
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
	printf("== 4. FIND ELEMENTS                   ==\n");
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

//SF Ten algorytm znajduje tylko pierwsze wystapienie poszukiwanego obiektu, a innych wystapien - nie.

// JN Poprawilem algorytm ze zwraca liste zgodnych elementow i je wyswietla
// dodalem rowniez opcje szukania po roku urodzenia i kierunku studiow
static void ui_find_elements() {
	handler_verify_for_fatal_errors();
	if (handler_is_stack_empty()) return;

	printf("Search by:");
	printf("\n1. Surname");
	printf("\n2. Birth year");
	printf("\n3. Field of study");
	printf("\nChoose: ");
	int chosen_option;
	scanf_s("%d", &chosen_option);
	while (getchar() != '\n') {};

	void** found_items = NULL;
	char* target_surname = NULL;

	size_t count = 0;

	switch (chosen_option) {
	case 1:
		printf("\nEnter surname to search: ");
		target_surname = util_scan_user_input();
		found_items = stack_find_all(
			student_compare_surname,
			target_surname,
			&count
		);
		break;
	case 2:
		printf("\nEnter birth year: ");
		int target_birth_year;
		scanf_s("%d", &target_birth_year);
		while (getchar() != '\n') {};
		found_items = stack_find_all(
			student_compare_birth_year,
			&target_birth_year,
			&count
		);
		break;
	case 3:
		printf("\n");
		student_print_fields_of_study();
		printf("Choose field of study: ");
		FIELD_OF_STUDY target_field_of_study;
		scanf_s("%d", &target_field_of_study);
		while (getchar() != '\n') {};
		found_items = stack_find_all(
			student_compare_field_of_study,
			&target_field_of_study,
			&count
		);
		break;
	default:
		message_error(
			ERROR_INVALID_ARGUMENT,
			"Invalid argument, try again",
			"ui_find_elements()"
		);
		return;
	}

	if (found_items && count > 0) {
		student_print_header();
		for (int i = 0; i < count; i++) {
			student_print(found_items[i]);
		}
		util_press_to_continue();
	}
	else {
		message_info("Students with the given criteria not found.");
	}

	if (target_surname) free(target_surname);
	free(found_items);
}

void ui_run_stack_menu(STACK* stack) {
	MENU_EVENT event = MAIN_MENU;

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
		case FIND_ELEMENTS:
			ui_find_elements(stack);
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
			ui_load_stack();
			break;
		case EXIT:
			return;
		default:
			break;
		}
	}
}

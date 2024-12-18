#include <stdbool.h>
#include "user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "my_student.h">
#include <string.h>

void ui_run_menu() {

	Stack stack = stack_initialize();

	MenuEvent event = MAIN_MENU;

	while (event != EXIT) {
		ui_print_menu();
		unsigned short selected_state;
		scanf_s("%hu", &selected_state);
		ui_on_event(&event, selected_state);
		ui_clear();
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
			ui_save_to_disk(stack);
			break;
		case LOAD_FROM_DISK:
			ui_load_from_disk(&stack);
			ui_press_any_key_to_continue();
			break;
		case EXIT:
			// TODO run corresponding function
			break;
		default:
			break;
		}
	}
}

void ui_print_stack(Stack stack) {
	if (stack.top == NULL) {
		printf("Stack is empty\n");
	}
	else {
		ui_print_student_header();
		while (stack.top != NULL) {
			MyStudent* student = (MyStudent*)stack.top->item;
			ui_student_print(student);

			StackNode* new_top = stack.top->next;
			stack.top = new_top;
		}
	}

	ui_press_any_key_to_continue();
}

void ui_print_top(Stack stack) {
	if (stack.top == NULL) {
		printf("Stack is empty\n");
	}
	else {
		ui_print_student_header();
		ui_student_print(stack.top->item);
	}

	ui_press_any_key_to_continue();
}

void ui_print_at_depth(Stack stack) {
	int depth = 1;
	printf("Enter depth: ");
	scanf_s("%d", &depth);
	void* item = stack_get(stack, depth);
	ui_clear();
	ui_print_student_header();
	ui_student_print(item);
	ui_press_any_key_to_continue();
}

void ui_push_to_stack(Stack* stack) {

	char surname[256];
	int birth_year;
	FieldOfStudy field_of_study;

	ui_clear();
	printf("ADDING STUDENT TO STACK\n");
	printf("Enter surname: ");
	scanf_s("%s", surname, 256);
	ui_clear();
	printf("Enter year of birth: ");
	scanf_s("%d", &birth_year);
	ui_clear();
	ui_print_fields_of_study();
	printf("Choose field of study: ");
	scanf_s("%d", &field_of_study);

	MyStudent* student = my_student_create(surname, birth_year, field_of_study);

	stack_push(stack, student);
}

void ui_pop_from_stack(Stack* stack) {\
	stack_pop(stack);
}

void ui_clear_stack(Stack* stack) {
	stack_clear(stack);
}

void ui_save_to_disk(Stack stack) {
	stack_save(stack, "backup.bin");
}

void ui_load_from_disk(Stack* stack) {
	stack_load(stack, "backup.bin");
}

void ui_on_event(
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

void ui_print_menu() {
	ui_clear();
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


void ui_clear() {
	system("cls");
}

void ui_press_any_key_to_continue() {
	printf("\nPress any key to continue... ");
	getch();
}

void ui_student_print(MyStudent* student) {
	char* field_of_study = ui_formatted_field_of_study(student->field_of_study);
	printf("%-25s| %-15d%| %s\n", student->surname, student->birth_year, field_of_study);
}

char* ui_formatted_field_of_study(FieldOfStudy field_of_study) {
	switch (field_of_study) {
	case COMPUTER_SCIENCE:
		return "Computer Science";
	case MATH:
		return "Mathematics";
	case PSYCHOLOGY:
		return "Psychology";
	case LAW:
		return "Law";
	case MEDICINE:
		return "Medicine";
	case PHYSICS:
		return "Physics";
	case PHILOSOPHY:
		return "Philosophy";
	default:
		exit(EXIT_FAILURE);
	}
}

void ui_print_fields_of_study() {
	printf("~~~~~ FIELDS OF STUDY ~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~ 1. Computer Science     ~\n");
	printf("~ 2. Mathematics          ~\n");
	printf("~ 3. Psychology           ~\n");
	printf("~ 4. Law                  ~\n");
	printf("~ 5. Medicine             ~\n");
	printf("~ 6. Physics              ~\n");
	printf("~ 7. Philosophy           ~\n");
	printf("~ 8. Mechanics            ~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ui_print_student_header() {
	printf("%-25s| %-15s%| %s\n", "SURNAME", "BIRTH YEAR", "FIELD OF STUDY");
	printf("----------------------------------------------------------\n");
}
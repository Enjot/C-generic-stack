#include <stdbool.h>
#include "user_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void ui_run_menu() {

	struct Stack* stack = stack_initialize();

	enum MenuState state = MAIN_MENU;

	while (state != EXIT) {
		ui_print_menu();
		unsigned short selected_state;
		scanf_s("%hu", &selected_state);
		ui_update_state(&state, selected_state);
		ui_clear();
		switch (state) {
		case MAIN_MENU:
			// option "0" - it's hidden
			break;
		case PRINT_STACK:
			ui_print_stack(*stack);
			ui_update_state(&state, MAIN_MENU);
			break;
		case PRINT_TOP:
			ui_print_top(*stack);
			break;
		case PRINT_AT_DEPTH:
			ui_print_at_depth(*stack);
			break;
		case PUSH_TO_STACK:
			// TODO run corresponding function
			ui_push_to_stack(stack);
			ui_update_state(&state, MAIN_MENU);
			break;
		case POP_FROM_STACK:
			ui_pop_from_stack(stack);
			break;
		case CLEAR_STACK:
			ui_clear_stack(stack);
			break;
		case SAVE_TO_DISK:
			break;
		case LOAD_FROM_DISK:
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
		printf("Stack elements:\n");
		while (stack.top != NULL) {
			printf("%s\n", stack.top->item);
			StackNode* new_top = stack.top->next;
			stack.top = new_top;
		}
	}

	ui_press_any_key_to_continue();
}

void ui_print_top(Stack stack) {
	if (stack.top != NULL) {
		printf("%s\n", stack.top->item);
	}
	else {
		printf("Stack is empty\n");
	}

	ui_press_any_key_to_continue();
}

void ui_print_at_depth(Stack* stack) {
	int depth = 1;
	printf("Enter depth: ");
	scanf_s("%d", &depth);
	StackNode* node = stack_get(&stack, depth);
	ui_clear();
	printf("%s", node->item);
	ui_press_any_key_to_continue();
}

void ui_push_to_stack(Stack* stack) {
	char* element = malloc(sizeof(char) * 64);

	ui_clear();
	printf("Enter your element: ");
	scanf_s("%s", element, 64);
	stack_push(stack, element);
}

void ui_pop_from_stack(Stack* stack) {
	stack_pop(stack);
	printf("Removed top element from stack\n\n");
	ui_print_stack(*stack);
}

void ui_clear_stack(Stack* stack) {
	stack_clear(stack);
}

void ui_save_to_disk(Stack stack) {

}

void ui_load_from_disk(Stack stack) {

}

static void ui_update_state(
	enum MenuState* state,
	unsigned short new_state
) {
	switch (new_state) {
	case 0:
		*state = MAIN_MENU;
		break;
	case 1:
		*state = PRINT_STACK;
		break;
	case 2:
		*state = PRINT_TOP;
		break;
	case 3:
		*state = PRINT_AT_DEPTH;
		break;
	case 4:
		*state = PUSH_TO_STACK;
		break;
	case 5:
		*state = POP_FROM_STACK;
		break;
	case 6:
		*state = CLEAR_STACK;
		break;
	case 7:
		*state = SAVE_TO_DISK;
		break;
	case 8:
		*state = LOAD_FROM_DISK;
		break;
	case 9:
		*state = EXIT;
		break;
	default:
		// TODO some invalid input handling
		*state = MAIN_MENU;
	}
}

void ui_print_menu() {
	ui_clear();
	printf("==============================\n");
	printf("====== STACK MANAGEMENT ======\n");
	printf("==============================\n");
	printf("== 1. PRINT STACK           ==\n");
	printf("== 2. PRINT TOP             ==\n");
	printf("== 3. PRINT AT DEPTH        ==\n");
	printf("==                          ==\n");
	printf("== 4. PUSH TO STACK         ==\n");
	printf("== 5. POP FROM STACK        ==\n");
	printf("== 6. CLEAR STACK           ==\n");
	printf("==                          ==\n");
	printf("== 7. SAVE TO DISK          ==\n");
	printf("== 8. LOAD FROM DISK        ==\n");
	printf("==                          ==\n");
	printf("== 9. EXIT                  ==\n");
	printf("==============================\n");
	printf("CHOOSE ACTION: ");
}


static void ui_clear() {
	system("cls");
}

static void ui_press_any_key_to_continue() {
	printf("\nPress eny key to continue... ");
	getch();
}
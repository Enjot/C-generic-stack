#include <stdbool.h>
#include "user_interface.h"
#include <stdio.h>
#include <stdlib.h>

void ui_run_menu() {

	enum MenuState state = MAIN_MENU;

	while (state != EXIT) {
		ui_print_menu();
		unsigned short chosen_state;
		scanf_s("%hu", &chosen_state);
		update_state(&state, chosen_state);
		switch (state) {
		case MAIN_MENU:
			break;
		case PRINT_STACK:
			// TODO run corresponding function
			break;
		case PRINT_TOP_FROM_STACK:
			// TODO run corresponding function
			break;
		case PRINT_FROM_STACK:
			// TODO run corresponding function
			break;
		case ADD_TO_STACK:
			// TODO run corresponding function
			break;
		case REMOVE_FROM_STACK:
			// TODO run corresponding function
			break;
		case EXIT:
			// TODO run corresponding function
			break;
		default:
			break;
		}
	}
}

static void update_state(
	enum MenuState* state,
	unsigned short new_state
) {
	ui_clear();
	switch (new_state) {
	case 0:
		*state = MAIN_MENU;
		break;
	case 1:
		*state = PRINT_STACK;
		break;
	case 2:
		*state = PRINT_TOP_FROM_STACK;
		break;
	case 3:
		*state = PRINT_FROM_STACK;
		break;
	case 4:
		*state = ADD_TO_STACK;
		break;
	case 5:
		*state = REMOVE_FROM_STACK;
		break;
	case 6:
		*state = EXIT;
		break;
	default:
		// TODO some error handling
		*state = MAIN_MENU;
	}
}

void ui_print_menu() {
	printf("==============================\n");
	printf("====== STACK MANAGEMENT ======\n");
	printf("==============================\n");
	printf("= 1. PRINT STACK             =\n");
	printf("= 2. PRINT TOP ELEMENT       =\n");
	printf("= 3. FIND ELEMENT            =\n");
	printf("= 4. ADD TO STACK            =\n");
	printf("= 5. REMOVE FROM STACK       =\n");
	printf("= 6. EXIT                    =\n");
	printf("==============================\n");
	printf("CHOOSE ACTION: ");
}

static void ui_clear() {
	system("cls");
}
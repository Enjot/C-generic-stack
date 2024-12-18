#include "stack.h"
#include "stdlib.h"
#include <stdbool.h>
#include <string.h>
#include "error_handler.h"

Stack stack_initialize() {
	Stack stack = { NULL };
	return stack;
}

bool stack_push(Stack* stack, void* item) {

	StackNode* node = malloc(sizeof(StackNode));

	if (!node) {
		// TODO replace with error handling function
		return false;
	}

	node->item = item;
	node->next = stack->top;
	stack->top = node;
	return true;
}

bool stack_pop(Stack* stack) {

	StackNode* old_top = stack->top;
	StackNode* new_top = stack->top->next;

	free(old_top);
	old_top = NULL;
	stack->top = new_top;
	return true;
}

void* stack_top(Stack stack) {
	return stack.top;
}

void stack_clear(Stack* stack) {
	while (stack->top != NULL) {
		stack_pop(stack);
	}
}

void* stack_get(Stack stack, const int depth) {

	int counter = 1;

	while (stack.top != NULL) {
		if (counter == depth) {
			return stack.top->item;
			break;
		}
		StackNode* new_top = stack.top->next;
		stack.top = new_top;
		counter++;
	}
}

bool stack_save_to_file(
	Stack* stack,
	const char* filename,
	size_t(*serialize)(void* item, FILE* file)
) {
	if (!stack || !filename || !serialize) return false; // TODO

	FILE* file = fopen(filename, "wb");
	if (file == NULL) error_open_file();

	StackNode* current_node = stack->top;
	while (current_node) {
		if (serialize(current_node->item, file) == 0) {
			fclose(file);
			return false;
		}
		current_node = current_node->next;
	}

	fclose(file);
	return true;
}

void stack_load_from_file(
	Stack* stack,
	const char* filename,
	void* (*deserialize)(FILE* file)
) {
	//if (!stack || !filename || !deserialize) exit(EXIT_FAILURE); // TODO

	FILE* file = fopen(filename, "rb");
	//if (file == NULL) exit(EXIT_FAILURE); // TODO

	Stack temp_stack = stack_initialize();

	while (!feof(file)) {
		void* item = deserialize(file);
		if (item) {
			if (!stack_push(&temp_stack, item)) {
				// TODO
				// Jeœli push siê nie powiedzie, zwalniamy dane
				/*if (stack->destroy) {
					stack->destroy(data);
				}*/
				fclose(file);
				//exit(EXIT_FAILURE);
				return false;
			}
			
		}
	}

	fclose(file);

	//stack_free(stack);

	while (temp_stack.top != NULL) {
		void* item = temp_stack.top->item;
		stack_push(stack, item);
		stack_pop(&temp_stack);
	}
}
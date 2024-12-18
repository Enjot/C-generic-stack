#include "stack.h"
#include "stdlib.h"
#include <stdbool.h>
#include <string.h>

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

void stack_save(Stack stack, const char* filename) {

	FILE* file = fopen(filename, "wb");

	StackNode* current = stack.top;

	while (current) {
		
	}

	size_t num_written = fwrite(stack.top->item, sizeof(char[64]), 1, file);

	fclose(file);
}

void stack_load(Stack* stack, const char* filename) {

	FILE* file = fopen(filename, "rb");

	char item[64];

	fread(&item, sizeof(char[64]), 1, file);
	printf("%s", item);

	fclose(file);
}
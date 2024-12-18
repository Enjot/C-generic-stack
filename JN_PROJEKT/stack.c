#include "stack.h"
#include "stdlib.h"
#include <stdbool.h>

Stack* stack_initialize() {
	Stack* stack = malloc(sizeof(Stack));
	if (stack != NULL) {
		stack->top = NULL;
	}
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

void* stack_top(Stack* stack) {
	return stack->top;
}

void stack_clear(Stack* stack) {
	while (stack->top != NULL) {
		stack_pop(stack);
	}
}

void* stack_get(Stack* stack) {

}
#include "stack.h"
#include "stdlib.h"
#include <stdbool.h>
#include <string.h>
#include "handler_error.h"
#include "handler_message.h"

Stack* stack_init(void (*destroy_item)(void* item)) {
	Stack* stack = malloc(sizeof(Stack));
	if (!stack) {
		error_memory_allocation("Couldn't allocate memory for stack");
		return NULL;
	}

	stack->top = NULL;
	stack->destroy_item = destroy_item;

	return stack;
}

void stack_destroy(Stack* stack) {
	if (stack) {
		stack_clear(stack);
		free(stack);
	}
}

bool stack_clear(Stack* stack) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return false;
	}

	void* item;
	while ((item = stack_pop(stack)) != NULL) {
		if (stack->destroy_item && item) {
			stack->destroy_item(item);
		}
	}
	return true;
}

bool stack_push(Stack* stack, void* item) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return false;
	}

	StackNode* node = malloc(sizeof(StackNode));

	if (!node) {
		error_memory_allocation("Couldn't allocate memory for new stack item");
		return false;
	}

	node->item = item;
	node->next = stack->top;
	stack->top = node;
	return true;
}

void* stack_pop(Stack* stack) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return NULL;
	}
	if (!stack->top) {
		return NULL;
	}

	StackNode* top_node = stack->top;
	void* top_item = top_node->item;
	stack->top = top_node->next;

	free(top_node);

	return top_item;
}

void* stack_peek(Stack* stack) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return NULL;
	}
	else if (!stack->top) {
		error_memory_not_allocated("Stack is empty");
		return NULL;
	}

	return stack->top->item;
}

void* stack_get_at_depth(Stack* stack, const int depth) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return NULL;
	}
	else if (!stack->top) {
		error_memory_not_allocated("Stack is empty");
		return NULL;
	}

	int counter = 1;
	StackNode* current = stack->top;
	while (current) {
		if (counter == depth) return current->item;
	
		current = current->next;
		counter++;
	}

	return NULL;
}

void* stack_find(
	Stack* stack,
	bool (*compare) (void* item, void* criteria),
	void* criteria
) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return NULL;
	}
	else if (!stack->top) {
		error_memory_not_allocated("Stack is empty");
		return NULL;
	}
	else if (!compare) {
		error_memory_not_allocated("Compare function is not initialized");
		return NULL;
	}

	StackNode* current = stack->top;
	while (current) {
		if (compare(current->item, criteria)) {
			return current->item;
		}
		current = current->next;
	}
	return NULL;
}

bool stack_save_to_file(
	Stack* stack,
	const char* filename,
	size_t(*serialize)(void* item, FILE* file)
) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return false;
	}
	if (!filename) {
		error_memory_not_allocated("File name is not initialized");
		return false;
	}
	if (!serialize) {
		error_memory_not_allocated("Serialize function is not initialized");
		return false;
	}

	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		error_file_open("Couldn't open file. Check if file exists");
		return false;
	}

	Stack* temp_stack = stack_init(NULL);
	if (!temp_stack) {
		error_memory_allocation("Couldn't initialize temporary stack");
		fclose(file);
		return false;
	}

	StackNode* current = stack->top;
	while (current) {
		if (!stack_push(temp_stack, current->item)) { // Error checking
			error_memory_allocation("Couldn't push item to temporary stack");
			stack_destroy(temp_stack);
			fclose(file);
			return false;
		}
		current = current->next;
	}

	void* item;
	while ((item = stack_pop(temp_stack)) != NULL) {
		size_t bytes_written = serialize(item, file);
		if (bytes_written == 0) {
			fclose(file);
			stack_destroy(temp_stack);
			error_memory_allocation("Serialization failed");
			return false;
		}
	}

	stack_destroy(temp_stack);
	fclose(file);
	return true;
}

bool stack_load_from_file(
	Stack* stack,
	const char* filename,
	void* (*deserialize)(FILE* file)
) {
	if (!stack) {
		error_memory_not_allocated("Stack is not initialized");
		return false;
	}
	if (!filename) {
		error_memory_not_allocated("File name is not initialized");
		return false;
	}
	if (!deserialize) {
		error_memory_not_allocated("Deserialize function is not initialized");
		return false;
	}

	FILE* file = fopen(filename, "rb");
	if (!file) {
		error_file_open("Couldn't open file. Check if file exists");
		return false;
	}

	stack_clear(stack);

	void* item;
	while ((item = deserialize(file)) != NULL) {
		if (!stack_push(stack, item)) {
			if (stack->destroy_item) {
				stack->destroy_item(item);
			}
			fclose(file);
			return false;
		}
	}

	fclose(file);
	return true;
}
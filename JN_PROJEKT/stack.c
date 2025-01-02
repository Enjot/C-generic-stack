#include "stack.h"
#include "stdlib.h"
#include "handler_error.h"
#include "handler_message.h"
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

Stack* stack_init(void (*destroy_item)(void* item)) {
	Stack* stack = malloc(sizeof(Stack));
	if (!stack) {
		error_memory_allocation("Couldn't allocate memory for stack", "stack_init()");
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
		error_null_pointer("Stack is not initialized", "stack_clear()");
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
		error_null_pointer("Stack is not initialized", "stack_push()");
		return false;
	}

	StackNode* node = malloc(sizeof(StackNode));

	if (!node) {
		error_memory_allocation("Couldn't allocate memory for new stack item", "stack_push()");
		return false;
	}

	node->item = item;
	node->next = stack->top;
	stack->top = node;
	return true;
}

void* stack_pop(Stack* stack) {
	if (!stack) {
		error_null_pointer("Stack is not initialized", "stack_pop()");
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
		error_null_pointer("Stack is not initialized", "stack_peek()");
		return NULL;
	}
	else if (!stack->top) {
		error_null_pointer("First stack element is not initialized", "stack_peek()");
		return NULL;
	}

	return stack->top->item;
}

void* stack_get_at_depth(Stack* stack, const int depth) {
	if (!stack) {
		error_null_pointer("Stack is not initialized", "stack_get_at_depth()");
		return NULL;
	}
	else if (!stack->top) {
		error_null_pointer("First stack element is not initialized", "stack_get_at_depth()");
		return NULL;
	}
	else if (depth <= 0) {
		error_invalid_argument("Depth must be greater than 0", "stack_get_at_depth()");
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
		error_null_pointer("Stack is not initialized", "stack_find()");
		return NULL;
	}
	else if (!stack->top) {
		error_null_pointer("Stack is empty", "stack_find()");
		return NULL;
	}
	else if (!compare) {
		error_null_pointer("Compare function is not initialized", "stack_find()");
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
	bool(*serialize)(void* item, FILE* file)
) {
	if (!stack) {
		error_null_pointer("Stack is not initialized", "stack_save_to_file()");
		return false;
	}
	if (!filename) {
		error_null_pointer("File name is not initialized", "stack_save_to_file()");
		return false;
	}
	if (!serialize) {
		error_null_pointer("Serialize function is not initialized", "stack_save_to_file()");
		return false;
	}

	FILE* file = fopen(filename, "wb");
	if (!file) {
		error_file_open("Couldn't open file. It may not exist or be blocked by another process", "stack_save_to_file()");
		return false;
	}

	//SF Tu tworzy Pan drugi stos, prawdopodobnie, zeby uniknac inwersji. Jednak jednoczesnie operowac dwoma kontenerami zamiast jednego - jest to
	//niedopuszczalna plata za unikniecie inwersji. Prosze pomyslec nad innymi rozwiazaniami, ktore by operowali tylko jedna struktura danych i mieli by 
	//O(n) odwolan do elementow stosu przy zapisie/odczycie.

	// JN wprowadzi³em zmiany do dzia³ania algorytmu, usun¹³em tworzenie drugiego stacku,
	// teraz od razu tworzony jest stack z w³aœciw¹ kolejnoœci¹ elementów
	StackNode* current = stack->top;
	while (current) {
		if (!serialize(current->item, file)) {
			fclose(file);
			error_memory_allocation("Serialization failed", "stack_save_to_file()");
			return false;
		}
		current = current->next;
	}

	fclose(file);
	return true;
}

static bool file_is_empty(FILE* file) {
	if (file == NULL) {
		return true;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, 0, SEEK_SET);

	return (size == 0);
}

bool stack_load_from_file(
	Stack* stack,
	const char* filename,
	void* (*deserialize)(FILE* file)
) {
	if (!stack) {
		error_null_pointer("Stack is not initialized", "stack_load_from_file()");
		return false;
	}
	if (!filename) {
		error_null_pointer("Filename is not initialized", "stack_load_from_file()");
		return false;
	}
	if (!deserialize) {
		error_null_pointer("Deserialize function is not initialized", "stack_load_from_file()");
		return false;
	}

	FILE* file = fopen(filename, "rb");
	if (!file) {
		error_file_open("Couldn't open file. It may not exist or be blocked by another process", "stack_load_from_file()");
		return false;
	}
	if (file_is_empty(file)) {
		error_file_empty("File is empty, can't load data from it", "stack_load_from_file()");
		fclose(file);
		return false;
	}

	stack_clear(stack);

	void* first_item = deserialize(file);
	if (!first_item) {
		return false;
	}

	StackNode* current = malloc(sizeof(StackNode));
	if (!current) {
		return false;
	}

	current->item = first_item;

	stack->top = current;

	while (true) {

		void* item = deserialize(file);
		if (!item) {
			break;
		}
		StackNode* node = malloc(sizeof(StackNode));
		if (!node) {
			free(item);
			break;
		}

		node->item = item;
		node->next = NULL;
		current->next = node;
		current = node;
	}

	fclose(file);
	return true;
}
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct StackNode {
    void* item;
    struct StackNode* next;
} StackNode;

typedef struct  {
    struct StackNode* top;
	void(*destroy_item)(void* item);
} Stack;

Stack* stack_init(void (*destroy_item)(void* item));
void stack_destroy(Stack* stack);
bool stack_clear(Stack* stack);

bool stack_push(Stack* stack, void* item);
void* stack_pop(Stack* stack);

void* stack_peek(Stack* stack);
void* stack_get_at_depth(Stack* stack, const int depth);

void* stack_find(
	Stack* stack,
	bool (*compare)(void* item, void* criteria),
	void* criteria
);

bool stack_save_to_file(
	Stack* stack,
	const char* filename,
	bool(*serialize)(void* item, FILE* file)
);
bool stack_load_from_file(
	Stack* stack,
	const char* filename,
	void* (*deserialize)(FILE* file)
);
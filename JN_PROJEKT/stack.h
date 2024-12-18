#pragma once

#include <stdio.h>
#include "stdbool.h"

typedef struct StackNode {
    void* item;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    struct StackNode* top;
} Stack;

Stack stack_initialize();

bool stack_push(Stack* stack, void* item);

bool stack_pop(Stack* stack);

void* stack_top(Stack* stack);

void stack_clear(Stack* stack);

void* stack_get(Stack stack, int depth);

// Save the stack to a file
int stack_save(Stack* stack, const char* filename);

// Load the stack from a file
struct Stack* stack_load(const char* filename);
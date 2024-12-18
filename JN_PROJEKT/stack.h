#pragma once

#include <stdio.h>
#include "stdbool.h"

typedef struct StackNode {
    void* item;
    struct StackNode* next;
} StackNode;

typedef struct  {
    struct StackNode* top;
} Stack;

Stack stack_initialize();

bool stack_push(Stack* stack, void* item);
bool stack_pop(Stack* stack);
void stack_clear(Stack* stack);

void* stack_top(Stack stack);
void* stack_get(Stack stack, const int depth);

void stack_save(Stack stack, const char* filename);
void stack_load(Stack* stack, const char* filename);
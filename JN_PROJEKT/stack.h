#pragma once
#include <stdbool.h>
#include <stdio.h>
#include "util.h"

typedef struct STACK_NODE {
    void *item;
    struct STACK_NODE *next;
} STACK_NODE;

typedef struct STACK {
    STACK_NODE *top;

    void (*destroy_item)(void *item);
} STACK;


extern STACK *stack;
extern const char *filename;
extern FILE* file;

STACK *stack_init(void (*destroy_item)(void *item));

void stack_destroy();

RESULT stack_clear();

RESULT stack_push(void *item);

void *stack_pop();

void *stack_peek();

void *stack_get_at_depth(int depth);

void **stack_find_all(
    bool (*compare)(void *item, void *criteria),
    void *criteria,
    size_t *out_count
);

RESULT stack_save_to_file(RESULT (*serialize)(void *item, FILE *file));

RESULT stack_load_from_file(void * (*deserialize)(FILE *file));

bool stack_is_empty();
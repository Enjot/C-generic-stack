#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "handler.h"
#include "message.h"

STACK *stack = NULL;
const char *filename = "backup.bin";
FILE *file = NULL;

STACK *stack_init(void (*destroy_item)(void *item)) {
    STACK *stack = malloc(sizeof(STACK));

    if (!stack) return NULL;

    stack->top = NULL;
    stack->destroy_item = destroy_item;

    return stack;
}

void stack_destroy() {
    if (stack) {
        stack_clear(stack);
        free(stack);
    }
}

RESULT stack_clear() {
    void *item;
    while ((item = stack_pop(stack)) != NULL) {
        if (stack->destroy_item && item) {
            stack->destroy_item(item);
        }
    }
    return SUCCESS;
}

RESULT stack_push(void *item) {
    handler_verify_for_fatal_errors();

    STACK_NODE *node = malloc(sizeof(STACK_NODE));

    if (!node) {
        message_error(
            ERROR_MEMORY_ALLOCATION,
            "Couldn't allocate memory for new stack item",
            "stack_push()"
        );
        return SUCCESS;
    }

    node->item = item;
    node->next = stack->top;
    stack->top = node;
    return SUCCESS;
}

void *stack_pop() {
    handler_verify_for_fatal_errors();

    if (!stack->top) return NULL;
    STACK_NODE *top_node = stack->top;
    void *top_item = top_node->item;
    stack->top = top_node->next;

    free(top_node);

    return top_item;
}

void *stack_peek() {
    handler_verify_for_fatal_errors();
    if (handler_is_stack_empty()) return NULL;

    return stack->top->item;
}

void *stack_get_at_depth(const int depth) {
    handler_verify_for_fatal_errors();
    if (handler_is_stack_empty()) return NULL;

    if (depth <= 0) {
        message_error(
            ERROR_INVALID_ARGUMENT,
            "Depth must be greater than 0",
            "stack_get_at_depth()"
        );
        return NULL;
    }

    int counter = 1;
    const STACK_NODE *current = stack->top;
    while (current) {
        if (counter == depth) return current->item;
        current = current->next;
        counter++;
    }

    return NULL;
}

void **stack_find_all(
    bool (*compare)(void *item, void *criteria),
    void *criteria,
    size_t *out_count
) {
    handler_verify_for_fatal_errors();
    if (handler_is_stack_empty()) return NULL;

    if (!compare) {
        message_error(
            ERROR_NULL_POINTER,
            "Compare function is not initialized",
            "stack_find()"
        );
        return NULL;
    }

    if (!out_count) {
        message_error(ERROR_NULL_POINTER,
            "Output count pointer is NULL",
            "stack_find_all()"
        );
        return NULL;
    }
    *out_count = 0;

    size_t capacity = 1;
    void **matches = malloc(capacity * sizeof(void *));
    if (!matches) {
        message_error(
            ERROR_MEMORY_ALLOCATION,
            "Couldn't allocate memory for stack elements",
            "stack_find_all()"
        );
        return NULL;
    }

    const STACK_NODE *current = stack->top;
    while (current) {
        if (compare(current->item, criteria) == true) {
            if (*out_count >= capacity) {
                const size_t new_capacity = capacity * 2;
                void **new_items = realloc(matches, new_capacity * sizeof(void *));
                if (!new_items) {
                    message_error(
                        ERROR_MEMORY_ALLOCATION,
                        "Couldn't allocate memory for stack elements",
                        "stack_find_all()"
                    );
                    free(matches);
                    return NULL;
                }
                matches = new_items;
                capacity = new_capacity;
            }
            matches[*out_count] = current->item;
            (*out_count)++;
        }
        current = current->next;
    }

    if (*out_count == 0) {
        free(matches);
        return NULL;
    }

    void** final_matches = realloc(matches, *out_count * sizeof(void *));
    if (final_matches) {
        matches = final_matches;
    }
    return matches;
}

RESULT stack_save_to_file(RESULT (*serialize)(void *item, FILE *file)) {
    handler_verify_for_fatal_errors();
    if (handler_is_stack_empty()) return FAILURE;

    if (!serialize) {
        message_error(
            ERROR_NULL_POINTER,
            "Serialize function is not initialized",
            "stack_save_to_file()"
        );
        return FAILURE;
    }

    fopen_s(&file, filename, "wb");
    if (!handler_is_file()) return FAILURE;

    //SF Tu tworzy Pan drugi stos, prawdopodobnie, zeby uniknac inwersji. Jednak jednoczesnie operowac dwoma kontenerami zamiast jednego - jest to
    //niedopuszczalna plata za unikniecie inwersji. Prosze pomyslec nad innymi rozwiazaniami, ktore by operowali tylko jedna struktura danych i mieli by
    //O(n) odwolan do elementow stosu przy zapisie/odczycie.

    // JN wprowadzilem zmiany do dzialania algorytmu, usunalem tworzenie drugiego stosu,
    // teraz od razu tworzony jest stos z wlasciwa kolejnoscia elementow
    const STACK_NODE *current = stack->top;
    while (current) {
        if (serialize(current->item, file) == FAILURE) {
            fclose(file);
            message_error(
                ERROR_MEMORY_ALLOCATION,
                "Serialization failed",
                "stack_save_to_file()"
            );
            return FAILURE;
        }
        current = current->next;
    }

    fclose(file);
    return SUCCESS;
}

RESULT stack_load_from_file(void * (*deserialize)(FILE *file)) {
    handler_verify_for_fatal_errors();

    if (!deserialize) {
        message_error(
            ERROR_NULL_POINTER,
            "Deserialize function is not initialized",
            "stack_load_from_file()"
        );
        return FAILURE;
    }

    fopen_s(&file, filename, "rb");
    if (!handler_is_file()) return FAILURE;
    if (handler_is_file_empty()) return FAILURE;

    stack_clear(stack);

    void *first_item = deserialize(file);
    if (!first_item) {
        fclose(file);
        return FAILURE;
    }

    STACK_NODE *current = malloc(sizeof(STACK_NODE));
    if (!current) {
        fclose(file);
        return FAILURE;
    }

    current->item = first_item;
    current->next = NULL;

    stack->top = current;

    while (true) {
        void *item = deserialize(file);
        if (!item) {
            break;
        }
        STACK_NODE *node = malloc(sizeof(STACK_NODE));
        if (!node) {
            if (stack->destroy_item) stack->destroy_item(item);
            break;
        }

        node->item = item;
        node->next = NULL;
        current->next = node;
        current = node;
    }

    fclose(file);
    return SUCCESS;
}

bool stack_is_empty() {
    return stack->top == NULL;
}

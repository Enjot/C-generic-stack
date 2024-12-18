#include "stack.h"
#include "unit_test.h"

//void test_file_read_write_and_write_to_memory() {
//	Stack stack = stack_initialize();
//	int a = 10, b = 20, c = 30, d = 40;
//
//	stack_push(&stack, &a);
//	stack_push(&stack, &b);
//	stack_push(&stack, &c);
//	stack_push(&stack, &d);
//
//	StackNode* current_node = stack.top;
//	while (current_node != NULL) {
//		int* number = (int*)current_node->item;
//		printf("%d\n", *number);
//		current_node = current_node->next;
//	}
//
//	stack_save_to_file(
//		&stack,
//		"unit_test.bin",
//
//	);
//
//	Stack new_stack = stack_initialize();
//	stack_load(&new_stack, sizeof(int), "stack.bin");
//
//	printf("===================================\n");
//
//	StackNode* new_current_node = new_stack.top;
//	while (new_current_node != NULL) {
//		int* number = (int*)new_current_node->item;
//		printf("%d\n", *number);
//		new_current_node = new_current_node->next;
//	}
//}
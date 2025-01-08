#include "user_interface.h"
#include "stack.h"
#include "my_student.h"
#include "util.h"
#include "handler.h"

//SF controll leak of memory
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {
	stack = stack_init(student_free);

	ui_run_stack_menu();

	handler_free_resources();

	//SF
	if (_CrtDumpMemoryLeaks())
		printf("LEAK OF MEMORY!!!!!!!!!!!!!\n");

	util_press_to_continue();
	return EXIT_SUCCESS;
}

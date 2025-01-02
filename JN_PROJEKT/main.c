#include "user_interface.h"
#include "stack.h"

//SF controll leak of memory
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	ui_run_menu();

	//SF
	if (_CrtDumpMemoryLeaks())
		printf("LEAK OF MEMORY!!!!!!!!!!!!!\n");

	return 0;
}
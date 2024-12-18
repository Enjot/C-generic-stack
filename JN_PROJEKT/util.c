
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

void util_clear_screen() {
	system("cls");
}

void util_press_any_key_to_continue() {
	printf("\nPress any key to continue... ");
	getch();
}
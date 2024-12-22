#include <stdlib.h>
#include "util.h"

void message_generic(char* message) {
	printf("%s\n", message);
	util_press_any_key_to_continue();
}
#pragma once
#include <stdlib.h>
#include <stdio.h>

void util_clear_screen();
void util_press_any_key_to_continue();
char* util_scan_user_input(FILE* file);

char* read_line();
#pragma once

typedef enum MENU_EVENT {
    MAIN_MENU = 99,
    PRINT_STACK = 1,
    PRINT_TOP = 2,
    PRINT_AT_DEPTH = 3,
    FIND_ELEMENTS = 4,
    PUSH_TO_STACK = 5,
    POP_FROM_STACK = 6,
    CLEAR_STACK = 7,
    SAVE_TO_DISK = 8,
    LOAD_FROM_DISK = 9,
    EXIT = 0
} MENU_EVENT;

void ui_run_stack_menu();
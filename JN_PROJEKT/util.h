#pragma once


// JN struktura ta wraz z biblioteką stdbool.h pomagaja szybko
// okreslic jaki jest kontekst zwracanej wartosci
// niz gdyby wszedzie byl zwracany typ "int"
typedef enum {
    SUCCESS = 0,
    FAILURE = 1,
} RESULT;

void util_clear_screen();

void util_press_to_continue();

char *util_scan_user_input();

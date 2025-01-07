#include <stdlib.h>
#include "handler.h"
#include "message.h"
#include "stack.h"

// SF Zadna z funkcji obslugi bladow i komunikatow nie zwalnia zasobow aplikacji
// w przypadku awaryjnego zakonczenia zadania.
// Oznacza to, ze albo zasoby nie beda zwolnione przez kod aplikacji,
// albo Pan po raz kazdy powinien pisac linii kodu po zwolnieniu zasobow przed
// wywolaniem tych funkcji.

// JN wprowadzilem zmiany, uczynilem stos i plik zmiennymi globalnymi i funkcje ktora
// zwalnia pamiec i zamyka aplikacje w przypadku bledu krytycznego, pozostale zmienne
// alokowane lokalnie, sa sprawdzane i w razie bledu dealokowane lokalnie i zwracana
// jest wtedy odpowiednia wartosc (RESULT FAILURE, bool false lub NULL wskaznik)
// i funkcja ktora wywolala ta funkcje (ktora zwrocila blad) decyduje co z tym zrobic
// dzieki czemu program jest bardziej elastyczny niz gdyby sie zamykal przy np.
// braku istniejacego pliku, obecnie zwraca komunikat i mozna uzywac programu dalej
// i sprobowac ponownie

static void handler_force_exit() {
    if (stack) stack_destroy(stack);
    // JN nie zwalniam filename poniewaz jest const (zmienna nie jest alokowana dynamicznie)
    if (file) fclose(file);
    exit(EXIT_FAILURE);
}

void handler_verify_for_fatal_errors() {
    if (!stack) {
        handler_force_exit();
    }
}

bool handler_is_stack_empty() {
    if (!stack->top) {
        message_info("Stack is empty");
        return true;
    }
    return false;
}

bool handler_is_file() {
    if (!file) {
        message_error(
            ERROR_FILE_OPEN,
            "Couldn't open file. It may not exist or be blocked by another process",
            "stack_save_to_file()"
        );
        return false;
    }
    return true;
}

// wywoluje ta funkcje tylko po tym jak juz uzylem wczesniej "handler_is_file"
bool handler_is_file_empty() {
    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    if (size == 0) {
        message_error(
            ERROR_FILE_IS_EMPTY,
            "File is empty, can't load data from it",
            "stack_load_from_file()"
        );
        fclose(file);
        return true;
    }
    return false;
}
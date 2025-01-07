#pragma once
#include <stdbool.h>
#include "util.h"

typedef enum {
    COMPUTER_SCIENCE = 1,
    MATH = 2,
    PSYCHOLOGY = 3,
    LAW = 4,
    MEDICINE = 5,
    PHYSICS = 6,
    PHILOSOPHY = 7,
    MECHANICS = 8
} FIELD_OF_STUDY;

typedef struct MY_STUDENT {
    char *surname;
    int birth_year;
    FIELD_OF_STUDY field_of_study;
} MY_STUDENT;

// Creation
MY_STUDENT *student_create(
    char *surname,
    int birth_year,
    FIELD_OF_STUDY field_of_study
);

void student_free(MY_STUDENT *student);

// Serialization
RESULT student_serialize(void *item);

void *student_deserialize();

// UI related
void student_print(const MY_STUDENT *student);

void student_print_fields_of_study();

void student_print_header();

bool student_compare_surname(MY_STUDENT *student, char *surname);

bool student_compare_birth_year(MY_STUDENT *student, int birth_year);

bool student_compare_field_of_study(MY_STUDENT *student, FIELD_OF_STUDY field_of_study);

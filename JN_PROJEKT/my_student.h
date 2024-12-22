#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

typedef enum FieldOfStudy {
	COMPUTER_SCIENCE = 1,
	MATH = 2,
	PSYCHOLOGY = 3,
	LAW = 4,
	MEDICINE = 5,
	PHYSICS = 6,
	PHILOSOPHY = 7,
	MECHANICS = 8
} FieldOfStudy;

typedef struct {
	char* surname;
	int birth_year;
	FieldOfStudy field_of_study;
} MyStudent;

// Creation
MyStudent* student_create(char* surname, int birth_year, FieldOfStudy field_of_study);
void student_free(MyStudent* student);

// Serialization
bool student_serialize(void* student, FILE* file);
void* student_deserialize(FILE* file);

// UI related
void student_print(MyStudent* student);
void student_print_fields_of_study();
void student_print_header();
#pragma once


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


MyStudent* my_student_create(char* surname, int birth_year, FieldOfStudy field_of_study);
void my_student_serialize(MyStudent* student, struct Buffer* output);
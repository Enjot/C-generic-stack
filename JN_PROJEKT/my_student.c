#include <stdlib.h>
#include <string.h>
#include "my_student.h"


MyStudent* my_student_create(char* surname, int birth_year, FieldOfStudy field_of_study) {

	MyStudent* student = malloc(sizeof(MyStudent));
	if (!student) {
		exit(EXIT_FAILURE);
	}

	size_t surname_length = strlen(surname);

	student->surname = malloc(sizeof(char) * surname_length + 1);

	if (!student->surname) {
		exit(EXIT_FAILURE); // TODO error handling
	}

	strcpy_s(student->surname, surname_length + 1, surname);

	student->birth_year = birth_year;

	student->field_of_study = field_of_study;

	return student;
}

void my_student_serialize(MyStudent* student, struct Buffer* output) {

}
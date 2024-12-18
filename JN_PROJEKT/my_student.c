#include <stdlib.h>
#include <string.h>
#include "my_student.h"


MyStudent* student_create(
	const char* surname,
	int birth_year,
	FieldOfStudy field_of_study
) {

	MyStudent* student = malloc(sizeof(MyStudent));
	if (!student) {
		exit(EXIT_FAILURE); // TODO
	}

	if (surname) {
		size_t surname_length = strlen(surname);
		student->surname = malloc(sizeof(char) * surname_length + 1);
		if (!student->surname) {
			exit(EXIT_FAILURE); // TODO error handling
		}
		strcpy_s(student->surname, surname_length + 1, surname);
	}
	else {
		exit(EXIT_FAILURE); // TODO
	}

	student->birth_year = birth_year;
	student->field_of_study = field_of_study;

	return student;
}

void student_free(MyStudent* student) {
	if (student) {
		if (student->surname) {
			free(student->surname);
		}
		free(student);
	}
}

size_t student_serialize(void* item, FILE* file) {
	
	if (!item || !file) return 0; // TODO

	MyStudent* student = (MyStudent*)item;

	size_t surname_length = student->surname ? strlen(student->surname) : 0;

	if (fwrite(&surname_length, sizeof(size_t), 1, file) != 1) return 0;

	if (surname_length > 0) {
		if (fwrite(student->surname, sizeof(char), surname_length, file) != surname_length) return 0;
	}

	if (fwrite(&student->birth_year, sizeof(int), 1, file) != 1) return 0;

	if (fwrite(&student->field_of_study, sizeof(FieldOfStudy), 1, file) != 1) return 0;

	return 1;
}

void* student_deserialize(FILE* file) {
	if (!file) return NULL; // TODO

	size_t surname_length;

	
	if (fread(&surname_length, sizeof(size_t), 1, file) != 1) return NULL;

	char* surname = NULL;
	if (surname_length > 0) {
		surname = malloc(sizeof(char) * (surname_length + 1));
		if (!surname) {
			return NULL;
		}

		if (fread(surname, sizeof(char), surname_length, file) != surname_length) {
			free(surname);
			return NULL;
		}
		surname[surname_length] = '\0';
	}

	int birth_year;
	if (fread(&birth_year, sizeof(int), 1, file) != 1) {
		if (surname) free(surname);
		return NULL;
		//exit(EXIT_FAILURE);
	}

	int field_int;
	if (fread(&field_int, sizeof(int), 1, file) != 1) {
		if (surname) free(surname);
		return NULL;
		//exit(EXIT_FAILURE);
	}

	FieldOfStudy field_of_study = (FieldOfStudy)field_int;

	MyStudent* student = student_create(surname, birth_year, field_of_study);

	return student;
}

void student_print(MyStudent* student) {
	char* field_of_study = student_formatted_field_of_study(student->field_of_study);
	printf("%-25s| %-15d%| %s\n", student->surname, student->birth_year, field_of_study);
}

char* student_formatted_field_of_study(FieldOfStudy field_of_study) {
	switch (field_of_study) {
	case COMPUTER_SCIENCE:
		return "Computer Science";
	case MATH:
		return "Mathematics";
	case PSYCHOLOGY:
		return "Psychology";
	case LAW:
		return "Law";
	case MEDICINE:
		return "Medicine";
	case PHYSICS:
		return "Physics";
	case PHILOSOPHY:
		return "Philosophy";
	default:
		exit(EXIT_FAILURE);
	}
}

void student_print_fields_of_study() {
	printf("~~~~~ FIELDS OF STUDY ~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~ 1. Computer Science     ~\n");
	printf("~ 2. Mathematics          ~\n");
	printf("~ 3. Psychology           ~\n");
	printf("~ 4. Law                  ~\n");
	printf("~ 5. Medicine             ~\n");
	printf("~ 6. Physics              ~\n");
	printf("~ 7. Philosophy           ~\n");
	printf("~ 8. Mechanics            ~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void student_print_header() {
	printf("%-25s| %-15s%| %s\n", "SURNAME", "BIRTH YEAR", "FIELD OF STUDY");
	printf("----------------------------------------------------------\n");
}
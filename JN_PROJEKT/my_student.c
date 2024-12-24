#include <stdio.h>
#include <stdlib.h>
#include "my_student.h"
#include "handler_error.h"


MyStudent* student_create(
	const char* surname,
	int birth_year,
	FieldOfStudy field_of_study
) {
	if (!surname) {
		error_null_pointer("No surname provided", "student_create()");
		return NULL;
	}

	MyStudent* student = malloc(sizeof(MyStudent));
	if (!student) {
		error_memory_allocation("Couldn't allocate memory for student", "student_create()");
		return NULL;
	}

	size_t surname_length = strlen(surname);
	student->surname = malloc(sizeof(char) * surname_length + 1);
	if (!student->surname) {
		error_memory_allocation("Couldn't allocate memory for student's surname", "student_create()");
		free(student);
		return NULL;
	}

	strcpy_s(student->surname, surname_length + 1, surname);

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

bool student_serialize(void* item, FILE* file) {

	if (!item) {
		error_null_pointer("Student is not initialized", "student_serialize()");
		return false;
	}
	if (!file) {
		error_null_pointer("File is not initialized", "student_serialize()");
		return false;
	}

	MyStudent* student = (MyStudent*)item;

	size_t surname_length = student->surname ? strlen(student->surname) : 0;

	if (fwrite(&surname_length, sizeof(size_t), 1, file) != 1) {
		error_file_write("Couldn't write surname length to file", "student_serialize()");
		return false;
	}

	if (surname_length > 0) {
		if (fwrite(student->surname, sizeof(char), surname_length, file) != surname_length) {
			error_file_write("Couldn't write surname to file", "student_serialize()");
			return false;
		};
	}

	if (fwrite(&student->birth_year, sizeof(int), 1, file) != 1) {
		error_file_write("Couldn't write year of birth to file", "student_serialize()");
		return false;
	}

	if (fwrite(&student->field_of_study, sizeof(FieldOfStudy), 1, file) != 1) {
		error_file_write("Couldn't write field of study to file", "student_serialize()");
		return false;
	}

	return true;
}

void* student_deserialize(FILE* file) {
	if (!file) {
		error_null_pointer("File is not initialized", "student_deserialize()");
		return NULL;
	}

	size_t surname_length;

	if (fread(&surname_length, sizeof(size_t), 1, file) != 1) {
		return NULL;
	}

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
	}

	int field_int;
	if (fread(&field_int, sizeof(int), 1, file) != 1) {
		if (surname) free(surname);
		error_memory_allocation("Couldn't read field of study", "student_deserialize()");
		return NULL;
	}

	FieldOfStudy field_of_study = (FieldOfStudy)field_int;

	MyStudent* student = student_create(surname, birth_year, field_of_study);
	if (!student) {
		if (surname) free(surname);
		return NULL;
	}
	return student;
}

static char* student_formatted_field_of_study(FieldOfStudy field_of_study) {
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
	case MECHANICS:
		return "Mechanics";
	default:
		return NULL;
	}
}

void student_print(MyStudent* student) {
	char* field_of_study = student_formatted_field_of_study(student->field_of_study);
	printf("%-25s| %-15d| %s\n", student->surname, student->birth_year, field_of_study);
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
	printf("%-25s| %-15s| %s\n", "SURNAME", "BIRTH YEAR", "FIELD OF STUDY");
	printf("----------------------------------------------------------\n");
}
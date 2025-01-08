#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_student.h"
#include "handler.h"
#include "message.h"
#include "stack.h"


MY_STUDENT *student_create(
    char *surname,
    const int birth_year,
    const FIELD_OF_STUDY field_of_study
) {
    if (!surname) {
        message_error(
            ERROR_NULL_POINTER,
            "No surname provided",
            "student_create()"
        );
        return NULL;
    }

    MY_STUDENT *student = malloc(sizeof(MY_STUDENT));
    if (!student) {
        message_error(
            ERROR_MEMORY_ALLOCATION,
            "Couldn't allocate memory for student",
            "student_create()"
        );
        return NULL;
    }

    student->surname = surname;
    student->birth_year = birth_year;
    student->field_of_study = field_of_study;

    return student;
}

void student_free(MY_STUDENT *student) {
    if (student) {
        if (student->surname) {
            free(student->surname);
        }
        free(student);
    }
}

RESULT student_serialize(void *item) {
    if (!item) {
        message_error(
            ERROR_NULL_POINTER,
            "Student is not initialized",
            "student_serialize()"
        );
        return FAILURE;
    }

    if (!handler_is_file()) return FAILURE;

    const MY_STUDENT *student = (MY_STUDENT *) item;

    const size_t surname_length = student->surname ? strlen(student->surname) : 0;

    if (fwrite(&surname_length, sizeof(size_t), 1, file) != 1) {
        message_error(
            ERROR_FILE_WRITE,
            "Couldn't write surname length to file",
            "student_serialize()"
        );
        return FAILURE;
    }

    if (surname_length > 0) {
        if (fwrite(student->surname, sizeof(char), surname_length, file) != surname_length) {
            message_error(
                ERROR_FILE_WRITE,
                "Couldn't write surname to file",
                "student_serialize()"
            );
            return FAILURE;
        };
    }

    if (fwrite(&student->birth_year, sizeof(int), 1, file) != 1) {
        message_error(
            ERROR_FILE_WRITE,
            "Couldn't write year of birth to file",
            "student_serialize()"
        );
        return FAILURE;
    }

    if (fwrite(&student->field_of_study, sizeof(FIELD_OF_STUDY), 1, file) != 1) {
        message_error(
            ERROR_FILE_WRITE,
            "Couldn't write field of study to file",
            "student_serialize()"
        );
        return FAILURE;
    }

    return SUCCESS;
}

void *student_deserialize(FILE *file) {
    if (!handler_is_file()) return NULL;

    size_t surname_length;

    if (fread(&surname_length, sizeof(size_t), 1, file) != 1) {
        return NULL;
    }

    char *surname = NULL;
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
        message_error(
            ERROR_MEMORY_ALLOCATION,
            "Couldn't read field of study",
            "student_deserialize()"
        );
        return NULL;
    }

    const FIELD_OF_STUDY field_of_study = field_int;

    MY_STUDENT *student = student_create(surname, birth_year, field_of_study);
    if (!student) {
        if (surname) free(surname);
        return NULL;
    }
    return student;
}

static char *student_formatted_field_of_study(const FIELD_OF_STUDY field_of_study) {
    switch (field_of_study) {
        case COMPUTER_SCIENCE: return "Computer Science";
        case MATH: return "Mathematics";
        case PSYCHOLOGY: return "Psychology";
        case LAW: return "Law";
        case MEDICINE: return "Medicine";
        case PHYSICS: return "Physics";
        case PHILOSOPHY: return "Philosophy";
        case MECHANICS: return "Mechanics";
        default: return NULL;
    }
}

void student_print(const MY_STUDENT *student) {
    char *field_of_study = student_formatted_field_of_study(student->field_of_study);
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

void student_print_all(void* criteria) {
    student_print_header();


}

bool student_compare_surname(const MY_STUDENT* student, char* surname) {
    if (!student || !surname) return false;
    return strcmp(student->surname, surname) == 0;
}

bool student_compare_birth_year(const MY_STUDENT* student, const int *birth_year) {
    if (!student || !birth_year) return false;
    return student->birth_year == *birth_year;
}

bool student_compare_field_of_study(const MY_STUDENT* student, const FIELD_OF_STUDY *field_of_study) {
    if (!student || !field_of_study) return false;
    return student->field_of_study == *field_of_study;
}
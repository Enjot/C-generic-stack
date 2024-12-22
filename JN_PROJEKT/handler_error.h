#pragma once

void error_file_open(const char* message, const char* source);
void error_file_read(const char* message, const char* source);
void error_file_write(const char* message, const char* source);

void error_null_pointer(const char* message, const char* source);
void error_memory_allocation(const char* message, const char* source);
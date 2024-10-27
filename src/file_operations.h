// Working with files

#pragma once

#include "defines.h"
#include "buffer_operations.h"

int check_file_existence(const char* path);
long long int get_file_size(const char* path);
char* get_file_text(const char* path);
void write_buffer_to_file(text_buffer* buffer);

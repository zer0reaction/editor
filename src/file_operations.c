// Working with files

#include "file_operations.h"
#include "buffer_operations.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Return 1 if file exists
int check_file_existence(const char* path) {
    if (access(path, F_OK) == 0) return 1;
    else return 0;
}

// Get file size in bytes, return 0 if it doesn't exist
long long int get_file_size(const char* path) {
    if (!check_file_existence(path)) return 0;

    FILE* file_ptr;
    file_ptr = fopen(path, "r");

    fseek(file_ptr, 0L, SEEK_END);
    long long int size = ftell(file_ptr);

    fclose(file_ptr);
    return size;
}

// Get all the text from the file
// If the file is not there, return NULL pointer
char* get_file_text(const char* path) {
    if (!check_file_existence(path)) return NULL;

    FILE* file_ptr;
    file_ptr = fopen(path, "r");

    long long int file_size = get_file_size(path);
    char* text = (char*)malloc(file_size);

    fread(text, 1, file_size, file_ptr);

    fclose(file_ptr);
    return text;
}

void write_buffer_to_file(text_buffer* buffer, const char* path) {
    FILE* file_ptr;

    // BAD
    file_ptr = fopen(path, "w");
    fprintf(file_ptr, "%s", "");

    fclose(file_ptr);
    file_ptr = fopen(path, "a");
    // BAD

    text_line* line = buffer->first_line;

    while (line != NULL) {
        fprintf(file_ptr, "%s\n", line->text);
        line = line->next_ptr;
    }

    fclose(file_ptr);
}

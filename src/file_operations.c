#include "file_operations.h"
#include "defines.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Return 1 if file exists
u8 check_file_existence(const char* path) {
    if (access(path, F_OK) == 0) return 1;
    else return 0;
}

// Get file size in bytes, return 0 if it doesn't exist
u64 get_file_size(const char* path) {
    if (!check_file_existence(path)) return 0;

    FILE* file_ptr;
    file_ptr = fopen(path, "r");

    fseek(file_ptr, 0L, SEEK_END);
    u64 size = ftell(file_ptr);

    fclose(file_ptr);
    return size;
}

// Get all the text from the file
s8* get_text(const char* path) {
    if (!check_file_existence(path)) return NULL;

    FILE* file_ptr;
    file_ptr = fopen(path, "r");

    u64 file_size = get_file_size(path);
    s8* text = (s8*)malloc(file_size);

    fread(text, 1, file_size, file_ptr);

    fclose(file_ptr);
    return text;
}

// Working with text

#include "text_operations.h"

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Appending given line to the end of the buffer
void append_line_to_buffer(struct text_buffer* buffer, 
                           struct text_line* line) {
    // If there are no lines in the buffer
    if (buffer->first_line == NULL) buffer->first_line = line;

    // If there is at least one line
    else {
        // Going to the last line
        struct text_line* last_line = buffer->first_line;
        while (last_line->next_ptr != NULL)
            last_line = last_line->next_ptr;

        // Assinging next_ptr
        last_line->next_ptr = line;

        // Assigning prev_ptr
        line->prev_ptr = last_line;
    }
}

// Creating a linked list from lines of text
void put_text_in_buffer(struct text_buffer* buffer, char* text) {
    // line_start - first character
    // line_end - one after last character
    char* line_start = text;
    char* line_end = strstr(text, "\n");

    // <= because there could be an empty line
    while (line_start <= line_end) {
        // Creating new line
        struct text_line* new_line = 
            (struct text_line*)malloc(sizeof(struct text_line));

        // Length without \0
        int new_line_length = line_start - line_end;

        char* new_line_text = (char*)malloc(new_line_length + 1);

        strncpy(new_line_text, line_start, new_line_length);
        new_line_text[new_line_length] = '\0';

        new_line->text = new_line_text;
        new_line->prev_ptr = NULL;
        new_line->next_ptr = NULL;

        append_line_to_buffer(buffer, new_line);

        line_start = line_end + 1;

        // If line_start now points ahead of the array
        if (line_start - text > (int)strlen(text))
            return;
        // If we are ok
        else {
            line_end = strstr(line_start, "\n");

            // If there are no lines left
            if (line_end == NULL)
                return;
        }
    }
}

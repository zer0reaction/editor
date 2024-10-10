// Working with text

#include "buffer_operations.h"

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Creating an empty buffer
text_buffer* create_buffer() {
    text_buffer* buffer = (text_buffer*)malloc(sizeof(text_buffer));

    buffer->first_line = NULL;
    buffer->current_line = NULL;
    buffer->mode = 0;

    buffer->offset_x = 0;
    buffer->offset_y = 0;

    // On what line the cursor is rendered, not the position in the window
    buffer->cursor_line = 0;
    buffer->cursor_pos = 0;

    buffer->needs_to_render = 1;

    return buffer;
}

// Appending given line to the end of the buffer
void append_line_to_buffer(text_buffer* buffer, text_line* line) {
    // If there are no lines in the buffer
    if (buffer->first_line == NULL) buffer->first_line = line;

    // If there is at least one line
    else {
        // Going to the last line
        text_line* last_line = buffer->first_line;
        while (last_line->next_ptr != NULL) last_line = last_line->next_ptr;

        // Assinging next_ptr
        last_line->next_ptr = line;

        // Assigning prev_ptr
        line->prev_ptr = last_line;
    }
}

text_line* create_new_line(char* text, int length) {
    text_line* new_line = (text_line*)malloc(sizeof(text_line));
    new_line->prev_ptr = NULL;
    new_line->next_ptr = NULL;
    new_line->length = length;

    char* new_line_text = (char*)malloc(new_line->length + 1);
    new_line_text[new_line->length] = '\0';

    strncpy(new_line_text, text, new_line->length);

    new_line->text=new_line_text;

    return new_line;
}

// Creating a linked list from lines of text
void put_text_in_buffer(text_buffer* buffer, char* text) {
    char* line_start = text;
    char* line_end = strstr(text, "\n");


    // If it is a single line
    if (line_end == NULL) {
        line_end = text + strlen(text);

        text_line* new_line = create_new_line(line_start, line_end - line_start);

        append_line_to_buffer(buffer, new_line);

        return;
    }

    // If there are multiple lines
    while (line_end != NULL) {
        text_line* new_line = create_new_line(line_start, line_end - line_start);

        append_line_to_buffer(buffer, new_line);

        line_start = line_end + 1;
        line_end = strstr(line_start, "\n");
    }

    // Dealing with the last line
    line_end = line_start + strlen(line_start);
    text_line* new_line = create_new_line(line_start, line_end - line_start);
    append_line_to_buffer(buffer, new_line);

    buffer->current_line = buffer->first_line;
}

void print_buffer_text(text_buffer* buffer) {
    if (buffer->first_line == NULL) printf("No text found!");

    text_line* current_line = buffer->first_line;

    while (current_line != NULL) {
        printf("%s\n", current_line->text);
        current_line = current_line->next_ptr;
    }
}

void free_buffer(text_buffer* buffer) {
    if (buffer != NULL) {
        text_line* current_line = buffer->first_line;
        text_line* next_line;

        while (current_line != NULL) {
            free(current_line->text);
            next_line = current_line->next_ptr;
            free(current_line);
            current_line = next_line;
        }

        free(buffer);
    }
}

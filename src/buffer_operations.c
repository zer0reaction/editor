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
    buffer->saved = 0;

    buffer->offset_x = 0;
    buffer->offset_y = 0;

    buffer->max_cursor_pos = 0;

    buffer->needs_to_render = 1;

    return buffer;
}

// Appending given line to the end of the buffer
void append_line_to_buffer(text_buffer* buffer, text_line* line) {
    // If there are no lines in the buffer
    if (buffer->first_line == NULL) { 
        buffer->first_line = line; 
        buffer->current_line = line; 
    }

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

    buffer->needs_to_render = 1; 
}

// Insert a line to the place of line_num (starting with 0)
// Returning the line the cursor is at now
text_line* insert_line_into_buffer(text_buffer* buffer, text_line* new_line, 
                                   int line_num) {
    text_line* current_line = buffer->first_line;
    text_line* prev_line = NULL;

    // Going to the line we need to insert to
    for (int i = 0; i < line_num; i++) {
        if (current_line == NULL) {
            printf("Error. Can't reach line\n");
            return NULL;
        }

        prev_line = current_line;
        current_line = current_line->next_ptr;
    }

    // Checking if we have prev line
    if (prev_line != NULL) {
        prev_line->next_ptr = new_line;
    }
    // if not, we are inserting to first line
    else {
        buffer->first_line = new_line;
    }

    // Setting lines for new line
    new_line->prev_ptr = prev_line;
    new_line->next_ptr = current_line;

    // Checking if we have current line
    if (current_line != NULL) {
        current_line->prev_ptr = new_line;
    }
    // if not, we are inserting to the last line

    buffer->needs_to_render = 1;
    return new_line;
}

// Delete a line (line_num starts with 0)
// Returning the line the cursor is at now
text_line* delete_line_from_buffer(text_buffer* buffer, int line_num) {
    text_line* to_delete = buffer->first_line;
    text_line* next_line;
    text_line* prev_line;

    // Checking if we have lines in the buffer
    if (buffer->first_line == NULL) {
        printf("Error. No lines in buffer\n");
        return NULL;
    }

    // Going to the line we need to delete
    for (int i = 0; i < line_num; i++) {
        if (to_delete->next_ptr == NULL) {
            printf("Error. Can't reach line\n");
            return NULL;
        }

        to_delete = to_delete->next_ptr;
    }
    next_line = to_delete->next_ptr;
    prev_line = to_delete->prev_ptr;

    // Checking if we have prev line
    if (prev_line != NULL) {
        prev_line->next_ptr = next_line;
    }
    // if not, that is the first line
    else {
        buffer->first_line = next_line;
    }

    // Checking if we have next line
    if (next_line != NULL) {
        next_line->prev_ptr = prev_line;
    }
    // if not, that is the last line

    // Freeing the memory
    if (to_delete != NULL) {
        free(to_delete->text);
        free(to_delete);
    }
    else printf("Error. Failed to free line\n");

    buffer->needs_to_render = 1;
    if (next_line != NULL) return next_line;
    else if (prev_line != NULL) return prev_line;
    else return NULL;
}

text_line* create_new_line(const char* text, int length) {
    text_line* new_line = (text_line*)malloc(sizeof(text_line));
    new_line->prev_ptr = NULL;
    new_line->next_ptr = NULL;
    new_line->last_cursor_pos = 0;

    char* new_line_text = (char*)malloc(length + 1);
    new_line_text[length] = '\0';

    strncpy(new_line_text, text, length);

    new_line->text=new_line_text;

    return new_line;
}

// Creating a linked list from lines of text
void put_text_in_buffer(text_buffer* buffer, char* text, char* path) {
    buffer->path = path;

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

void free_buffer(text_buffer* buffer) {
    if (buffer != NULL) {
        text_line* current_line = buffer->first_line;
        text_line* next_line;

        while (current_line != NULL) {
            printf("freeing current line text\n");
            free(current_line->text);
            next_line = current_line->next_ptr;
            printf("freeing current line\n");
            free(current_line);
            current_line = next_line;
        }

        printf("freeing buffer\n");
        free(buffer);
    }
}

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

void add_character_at_cursor(text_buffer* buffer, char c) {
    if (buffer->current_line == NULL) {
        text_line* new_line = create_new_line("", 0);
        append_line_to_buffer(buffer, new_line);
    }

    text_line* current_line = buffer->current_line;
    int cursor_pos = buffer->current_line->last_cursor_pos;

    char* new_text = (char*)malloc(strlen(current_line->text) + 2);
    new_text[strlen(current_line->text) + 1] = '\0';

    strncpy(new_text, current_line->text, cursor_pos);
    new_text[cursor_pos] = c;
    strncpy(new_text + cursor_pos + 1, current_line->text + cursor_pos, strlen(current_line->text) - cursor_pos);

    free(current_line->text);
    current_line->text = new_text;

    buffer->current_line->last_cursor_pos++;
    buffer->max_cursor_pos = current_line->last_cursor_pos;
    buffer->needs_to_render = 1;
}

void delete_character_before_cursor(text_buffer* buffer) {
    if (buffer->current_line == NULL || 
        strlen(buffer->current_line->text) == 0 ||
        buffer->current_line->last_cursor_pos == 0) return;


    text_line* current_line = buffer->current_line;
    int cursor_pos = buffer->current_line->last_cursor_pos;

    char* new_text = (char*)malloc(strlen(current_line->text));
    new_text[strlen(current_line->text) - 1] = '\0';

    strncpy(new_text, current_line->text, cursor_pos - 1);
    strncpy(new_text + cursor_pos - 1, current_line->text + cursor_pos, strlen(current_line->text) - cursor_pos);

    free(current_line->text);
    current_line->text = new_text;

    buffer->current_line->last_cursor_pos--;
    buffer->max_cursor_pos = current_line->last_cursor_pos;
    buffer->needs_to_render = 1;
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

// Working with text

#pragma once

struct text_line {
    struct text_line* prev_ptr;
    struct text_line* next_ptr;

    char* text;
    int length;
};

struct text_buffer {
    struct text_line* first_line;
};

void append_line_to_buffer(struct text_buffer* buffer, struct text_line* line);

struct text_line* create_new_line(char* text, int length);

void put_text_in_buffer(struct text_buffer* buffer, char* text);

void print_buffer_text(struct text_buffer* buffer);

void free_buffer(struct text_buffer* buffer);

// Working with text

#pragma once

struct text_line {
    struct text_line* prev_ptr;
    struct text_line* next_ptr;

    char* text;
};

struct text_buffer {
    struct text_line* first_line;
};

void put_text_in_buffer(struct text_buffer* buffer, char* text);

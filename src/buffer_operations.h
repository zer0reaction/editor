// Working with text

#pragma once

typedef struct text_line text_line;
typedef struct text_buffer text_buffer;

struct text_line {
    text_line* prev_ptr;
    text_line* next_ptr;

    int last_cursor_pos;

    char* text;
    int length;
};

struct text_buffer {
    text_line* first_line;
    text_line* current_line;

    int offset_x;
    int offset_y;

    int cursor_line;
    int max_cursor_pos;

    int mode; // 0 - normal, 1 - insert
    
    int needs_to_render;
};

text_buffer* create_buffer();
void append_line_to_buffer(text_buffer* buffer, text_line* line);
text_line* create_new_line(char* text, int length);
void put_text_in_buffer(text_buffer* buffer, char* text);
void print_buffer_text(text_buffer* buffer);
void free_buffer(text_buffer* buffer);

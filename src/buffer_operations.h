// Working with text

#pragma once

typedef struct text_line text_line;
typedef struct text_buffer text_buffer;

struct text_line {
    text_line* prev_ptr;
    text_line* next_ptr;

    int last_cursor_pos;

    char* text;
};

struct text_buffer {
    text_line* first_line;
    text_line* current_line;

    int offset_x;
    int offset_y;
    int max_cursor_pos;
    int mode; // 0 - normal, 1 - insert
    int needs_to_render;
    int saved;

    const char* path;
};

text_buffer* create_buffer();
text_line* create_new_line(const char* text, int length);

void append_line_to_buffer(text_buffer* buffer, text_line* line);
text_line* insert_line_into_buffer(text_buffer* buffer, text_line* new_line, 
                                   int line_num);
text_line* delete_line_from_buffer(text_buffer* buffer, int line_num);
text_line* insert_line_into_buffer(text_buffer* buffer, text_line* new_line, 
                                   int line_num);

void put_text_in_buffer(text_buffer* buffer, char* text, char* path);

void free_buffer(text_buffer* buffer);

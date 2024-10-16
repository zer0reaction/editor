// Moving cursor aroung, inserting text, etc

#pragma once

#include "defines.h"
#include "buffer_operations.h"

int get_cursor_line_num(text_buffer* buffer);
void snap_cursor(text_buffer* buffer);
void move_cursor_vertically(text_buffer* buffer, int offset);
void move_cursor_horizontally(text_buffer* buffer, int offset);

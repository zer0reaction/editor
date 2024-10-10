// Displaying stuff on the screen

#pragma once

#include "buffer_operations.h"
#include "raylib.h"

void init_display(const char* f_path, int f_size, Color* f_color, Color* b_color);
void display_buffer(text_buffer* buffer, int offset_x, int offset_y);

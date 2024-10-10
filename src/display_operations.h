// Displaying stuff on the screen

#pragma once

#include "buffer_operations.h"
#include "raylib.h"

void init_display(const char* f_path);
void end_display();
void display_buffer(text_buffer* buffer, int offset_x, int offset_y);

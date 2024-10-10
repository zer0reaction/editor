// Displaying stuff on the screen

#pragma once

#include "buffer_operations.h"
#include "raylib.h"

void display_buffer(text_buffer* buffer, int font_size, Color* font_color, Color* background_color, int offset_x, int offset_y);

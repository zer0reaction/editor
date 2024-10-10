// Displaying stuff on the screen

#include <stddef.h>
#include <stdio.h>

#include "raylib.h"
#include "display_operations.h"

Font font;
Color font_color;
Color background_color;

void init_display(const char* f_path, int f_size, Color* f_color, Color* b_color) {
    font = LoadFontEx(f_path, f_size, 0, 0);
    font_color = *f_color;
    background_color = *b_color;
}

void display_buffer(text_buffer* buffer, int offset_x, int offset_y) {
    text_line* current_line = buffer->first_line;

    ClearBackground(background_color);

    int screen_height = GetScreenHeight();

    // For each line
    while (current_line != NULL) {
        if (offset_y < screen_height && offset_y >= 0) {
            DrawTextEx(font, current_line->text, (Vector2){ (float)offset_x, (float)offset_y }, (float)font.baseSize, 0.0f, font_color);
        }
        else if (offset_y > screen_height) return;

        offset_y += font.baseSize;
        current_line = current_line->next_ptr;
    }
}

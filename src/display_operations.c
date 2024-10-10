// Displaying stuff on the screen

#include <stddef.h>
#include <stdio.h>

#include "raylib.h"
#include "display_operations.h"


void display_buffer(text_buffer* buffer, int font_size, Color* font_color, Color* background_color, int offset_x, int offset_y) {
    text_line* current_line = buffer->first_line;

    Font font = LoadFontEx("/usr/share/fonts/TTF/Hack-Regular.ttf", font_size, 0, 0);

    BeginDrawing();
    ClearBackground(*background_color);

    // For each line
    while (current_line != NULL) {
        DrawTextEx(font, current_line->text, (Vector2){ (float)offset_x, (float)offset_y }, (float)font_size, 0.0f, *font_color);
        offset_y += font_size;

        current_line = current_line->next_ptr;
    }

    EndDrawing();
}

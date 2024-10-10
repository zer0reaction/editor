// Displaying stuff on the screen

#include <stddef.h>
#include <stdio.h>

#include "raylib.h"
#include "display_operations.h"
#include "defines.h"

Font font;

void init_display(const char* f_path) {
    font = LoadFontEx(f_path, FONT_SIZE, 0, 0);
}

void end_display() {
    UnloadFont(font);
}

void display_buffer(text_buffer* buffer, int offset_x, int offset_y) {
    text_line* current_line = buffer->first_line;

    ClearBackground(BACKGROUND_COLOR);

    int screen_height = GetScreenHeight();

    int line_count = 0;

    // For each line
    while (current_line != NULL) {
        // If the line is on the screen
        if (offset_y < screen_height && offset_y >= 0) {
            DrawTextEx(font, current_line->text, (Vector2){ (float)offset_x, (float)offset_y }, (float)font.baseSize, 0.0f, FONT_COLOR);

            // Displaying cursor
            if (line_count == buffer->cursor_line) {
                DrawRectangle(buffer->cursor_pos * FONT_SIZE / 2, line_count * FONT_SIZE, FONT_SIZE / 2, FONT_SIZE, FONT_COLOR);

                char character_under_cursor[2];
                character_under_cursor[0] = current_line->text[buffer->cursor_pos];
                character_under_cursor[1] = '\n';

                DrawTextEx(font, character_under_cursor, 
                           (Vector2){ (float)offset_x + buffer->cursor_pos * FONT_SIZE, 
                           (float)offset_y }, (float)font.baseSize, 0.0f, BACKGROUND_COLOR);
            }
        }
        else if (offset_y > screen_height) return;

        offset_y += font.baseSize;
        current_line = current_line->next_ptr;
        line_count++;
    }
}

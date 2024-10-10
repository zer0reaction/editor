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

void display_buffer(text_buffer* buffer) {
    ClearBackground(BACKGROUND_COLOR);

    text_line* line = buffer->first_line;
    int screen_height = GetScreenHeight();
    int line_count = 0;

    int current_offset_x = buffer->offset_x;
    int current_offset_y = buffer->offset_y;

    // For each line
    while (line != NULL) {
        // If the line is on the screen
        if (current_offset_y < screen_height && current_offset_y >= 0) {
            DrawTextEx(font, line->text, (Vector2){ (float)current_offset_x, (float)current_offset_y }, (float)font.baseSize, 0.0f, FONT_COLOR);

            // Displaying cursor
            if (line_count == buffer->cursor_line) {
                int cursor_x = buffer->cursor_pos * FONT_SIZE / 2;
                int cursor_y = buffer->cursor_line * FONT_SIZE + buffer->offset_y;

                DrawRectangle(cursor_x, cursor_y, FONT_SIZE / 2, FONT_SIZE, FONT_COLOR);

                char character_under_cursor[2];
                character_under_cursor[0] = line->text[buffer->cursor_pos];
                character_under_cursor[1] = '\n';

                DrawTextEx(font, character_under_cursor, 
                           (Vector2){ (float)buffer->offset_x + buffer->cursor_pos * FONT_SIZE, 
                           (float)current_offset_y }, (float)font.baseSize, 0.0f, BACKGROUND_COLOR);
            }
        }
        else if (current_offset_y > screen_height) return;

        current_offset_y += font.baseSize;
        line = line->next_ptr;
        line_count++;
    }
}

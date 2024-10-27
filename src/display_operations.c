// Displaying stuff on the screen

#include <stddef.h>
#include <stdio.h>

#include "raylib.h"
#include "display_operations.h"
#include "cursor_operations.h"
#include "defines.h"

Font font;

void init_display(const char* f_path) {
    font = LoadFontEx(f_path, FONT_SIZE, 0, 0);
    SetExitKey(KEY_NULL);
}

void end_display() {
    UnloadFont(font);
}

void display_cursor(text_buffer* buffer) {
}

void display_buffer(text_buffer* buffer) {
    ClearBackground(BACKGROUND_COLOR);

    int screen_height = GetScreenHeight();

    int current_offset_x = buffer->offset_x;
    int current_offset_y = buffer->offset_y;
    int cursor_line = get_cursor_line_num(buffer);

    text_line* line = buffer->first_line;

    // For each line
    while (line != NULL) {
        // If the line is on the screen
        if (current_offset_y < screen_height && current_offset_y >= 0) {
            DrawTextEx(font, line->text, (Vector2){ (float)current_offset_x, 
            (float)current_offset_y }, (float)font.baseSize, 0.0f, FONT_COLOR);

            // Displaying cursor
            if (line == buffer->current_line) {
                int cursor_x = buffer->current_line->last_cursor_pos * 
                FONT_SIZE / 2 + buffer->offset_x;

                int cursor_y = cursor_line * FONT_SIZE + 
                buffer->offset_y;

                int cursor_width;
                if (buffer->mode == 1)
                    cursor_width = FONT_SIZE / 10;
                else 
                    cursor_width = FONT_SIZE / 2;

                DrawRectangle(cursor_x, cursor_y, cursor_width, FONT_SIZE, 
                CURSOR_COLOR);

                char character_under_cursor[2];
                character_under_cursor[0] = 
                line->text[buffer->current_line->last_cursor_pos];

                character_under_cursor[1] = '\n';

                // Draw text on top of cursor in normal mode
                if (buffer->mode == 0) {
                    DrawTextEx(font, character_under_cursor, 
                               (Vector2){ (float)cursor_x, (float)cursor_y }, 
                               (float)font.baseSize, 0.0f, BACKGROUND_COLOR);
                }
            }
        }
        else if (current_offset_y > screen_height) return;

        current_offset_y += font.baseSize;
        line = line->next_ptr;
    }
}

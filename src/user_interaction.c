// Keyboard handling basically

#include "buffer_operations.h"
#include "cursor_operations.h"
#include "defines.h"
#include "raylib.h"
#include <stdio.h>

void handle_keyboard(text_buffer* buffer) {
    // Normal mode stuff
    if (buffer->mode == 0) {
        int cursor_line = get_cursor_line_num(buffer);

        if (IsKeyPressed(KEY_I))
            buffer->mode = 1;

        else if (IsKeyPressed(KEY_J)) 
            move_cursor_vertically(buffer, -1);

        else if (IsKeyPressed(KEY_K)) 
            move_cursor_vertically(buffer, 1);

        else if (IsKeyPressed(KEY_H)) 
            move_cursor_horizontally(buffer, -1);

        else if (IsKeyPressed(KEY_L)) 
            move_cursor_horizontally(buffer, 1);

        else if (IsKeyPressed(KEY_O) && (IsKeyDown(KEY_LEFT_SHIFT) || 
                 IsKeyDown(KEY_RIGHT_SHIFT))) {
            text_line* new_line = create_new_line("", 0);
            buffer->current_line = insert_line_into_buffer(buffer, new_line, 
                                                           cursor_line);
            buffer->mode = 1;
            snap_cursor(buffer);
        }

        else if (IsKeyPressed(KEY_O)) {
            text_line* new_line = create_new_line("", 0);
            buffer->current_line = insert_line_into_buffer(buffer, new_line, 
                                                           cursor_line + 1);
            buffer->mode = 1;
            snap_cursor(buffer);
        }

        else if (IsKeyPressed(KEY_D) && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
            buffer->current_line = delete_line_from_buffer(buffer, cursor_line);
        }
    }

    // Insert mode stuff
    else if (buffer->mode == 1) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            buffer->mode = 0;
        }
        else if (IsKeyPressed(KEY_BACKSPACE)) {
            delete_character_before_cursor(buffer);
        }
        else if (IsKeyPressed(KEY_TAB)) {
            for (int i = 0; i < TAB_SPACES; i++)
                add_character_at_cursor(buffer, ' ');
        }

        char c = GetCharPressed();
        while (c) {
            add_character_at_cursor(buffer, c);
            c = GetCharPressed();
        }
    }
}

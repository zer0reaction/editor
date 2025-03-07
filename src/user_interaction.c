// Keyboard handling basically

#include "buffer_operations.h"
#include "cursor_operations.h"
#include "defines.h"
#include "file_operations.h"
#include "raylib.h"
#include <stdio.h>

void handle_keyboard(text_buffer* buffer) {
    // Normal mode stuff
    if (buffer->mode == 0) {
        int cursor_line = get_cursor_line_num(buffer);

        if (IsKeyPressed(KEY_I)) {
            buffer->mode = 1;
            buffer->needs_to_render = 1;
        }

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
            buffer->saved = 0;
            snap_cursor(buffer);
        }

        else if (IsKeyPressed(KEY_O)) {
            text_line* new_line = create_new_line("", 0);
            buffer->current_line = insert_line_into_buffer(buffer, new_line, 
                                                           cursor_line + 1);
            buffer->mode = 1;
            buffer->saved = 0;
            snap_cursor(buffer);
        }

        else if (IsKeyPressed(KEY_D) && 
                (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) {
            buffer->current_line = delete_line_from_buffer(buffer, cursor_line);
            buffer->saved = 0;
        }

        else if (IsKeyPressed(KEY_S) && 
                (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            if (buffer->path)
                write_buffer_to_file(buffer);
        }
    }

    // Insert mode stuff
    else if (buffer->mode == 1) {
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_CAPS_LOCK)) {
            buffer->mode = 0;
            buffer->needs_to_render = 1;
        } else if (IsKeyPressed(KEY_BACKSPACE) && buffer->current_line->last_cursor_pos == 0) {
            buffer->current_line = join_line_with_prev(buffer);
            buffer->saved = 0;
        } else if (IsKeyPressed(KEY_BACKSPACE)) {
            delete_character_before_cursor(buffer);
            buffer->saved = 0;
        } else if (IsKeyPressed(KEY_TAB)) {
            for (int i = 0; i < TAB_SPACES; i++)
                add_character_at_cursor(buffer, ' ');
            buffer->saved = 0;
        } else if (IsKeyPressed(KEY_ENTER)) {
            // TEMP
            buffer->current_line = shift_line_to_next(buffer);
            buffer->saved = 0;
        }

        char c = GetCharPressed();
        while (c) {
            add_character_at_cursor(buffer, c);
            c = GetCharPressed();
            buffer->saved = 0;
        }
    }
}

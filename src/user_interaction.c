// Keyboard handling basically

#include "buffer_operations.h"
#include "cursor_operations.h"
#include "raylib.h"
#include <stdio.h>

void handle_keyboard(text_buffer* buffer) {
    // Normal mode stuff
    if (buffer->mode == 0) {
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

        else if (IsKeyPressed(KEY_O)) {
            text_line* new_line = create_new_line("", 0);
            insert_line_into_buffer(buffer, new_line, buffer->cursor_line + 1);
            move_cursor_vertically(buffer, -1);
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

        char c = GetCharPressed();
        while (c) {
            printf("%i\n", c);
            add_character_at_cursor(buffer, c);
            c = GetCharPressed();
        }
    }
}

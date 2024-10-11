// Moving cursor aroung, inserting text, etc

#include "cursor_operations.h"
#include "buffer_operations.h"
#include "defines.h"
#include "raylib.h"

#include <stddef.h>
#include <stdio.h>

void move_cursor_vertically(text_buffer* buffer, int offset) {
    // If there is a line and we are in normal mode
    if (buffer->current_line != NULL && buffer->mode == 0) {
        // Moving up
        if (offset > 0) {
            for (int i = 0; i < offset; i++) {
                if (buffer->current_line->prev_ptr != NULL) {
                    buffer->current_line = buffer->current_line->prev_ptr;
                    buffer->cursor_line--;
                } else return;
            }


            // Moving screen down
            int current_cursor_relative_pos = buffer->cursor_line * FONT_SIZE + buffer->offset_y;

            if (current_cursor_relative_pos < 0)
                buffer->offset_y += -current_cursor_relative_pos;
        }

        // Moving down
        else if (offset < 0) {
            for (int i = 0; i < -offset; i++) {
                if (buffer->current_line->next_ptr != NULL) {
                    buffer->current_line = buffer->current_line->next_ptr;
                    buffer->cursor_line++;
                } else return;
            }

            // Moving screen up
            int current_cursor_relative_pos = buffer->cursor_line * FONT_SIZE + buffer->offset_y;

            if (current_cursor_relative_pos + FONT_SIZE >= GetScreenHeight())
                buffer->offset_y -= current_cursor_relative_pos + FONT_SIZE - GetScreenHeight();
        }

        buffer->needs_to_render = 1;
    }
}

// Moving cursor aroung, inserting text, etc

#include "cursor_operations.h"
#include "buffer_operations.h"
#include "defines.h"
#include "raylib.h"

#include <stddef.h>
#include <stdio.h>

void move_cursor_vertically(text_buffer* buffer, int offset) {
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
            if (buffer->cursor_line * FONT_SIZE + buffer->offset_y < 0)
                buffer->offset_y += FONT_SIZE;
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
            if (buffer->cursor_line * FONT_SIZE + buffer->offset_y >= GetScreenHeight())
                buffer->offset_y -= FONT_SIZE;
        }

        buffer->needs_to_render = 1;
    }
}

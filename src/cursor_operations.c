// Moving cursor aroung, inserting text, etc

#include "cursor_operations.h"
#include "buffer_operations.h"
#include "defines.h"
#include "raylib.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

// Change the offset so the cursor is visible from the top of the screen or from the bottom
void snap_cursor(text_buffer* buffer) {
    int current_cursor_relative_pos_y = buffer->cursor_line * FONT_SIZE + buffer->offset_y;

    // If the cursor is above window
    if (current_cursor_relative_pos_y < 0)
        buffer->offset_y += -current_cursor_relative_pos_y;
    // If the cursor is below
    else if (current_cursor_relative_pos_y + FONT_SIZE >= GetScreenHeight())
        buffer->offset_y -= current_cursor_relative_pos_y + FONT_SIZE - GetScreenHeight();
}

void move_cursor_vertically(text_buffer* buffer, int offset) {
    // If there is a line and we are in normal mode
    if (buffer->current_line != NULL) {
        // Moving up
        if (offset > 0) {
            for (int i = 0; i < offset; i++) {
                if (buffer->current_line->prev_ptr != NULL) {
                    buffer->current_line = buffer->current_line->prev_ptr;
                    buffer->cursor_line--;
                } else return;
            }
        }

        // Moving down
        else if (offset < 0) {
            for (int i = 0; i < -offset; i++) {
                if (buffer->current_line->next_ptr != NULL) {
                    buffer->current_line = buffer->current_line->next_ptr;
                    buffer->cursor_line++;
                } else return;
            }
        }

        // btw there is a bug in this
        if (buffer->max_cursor_pos <= (int)strlen(buffer->current_line->text)) {
            buffer->current_line->last_cursor_pos = buffer->max_cursor_pos;
        }
        else {
            buffer->current_line->last_cursor_pos = strlen(buffer->current_line->text);
        }

        snap_cursor(buffer);
        buffer->needs_to_render = 1;
    }
}

void move_cursor_horizontally(text_buffer* buffer, int offset) {
    // If there is a line and we are in normal mode
    if (buffer->current_line != NULL) {
        if (offset < 0) {
            if (buffer->current_line->last_cursor_pos + offset <= 0) {
                buffer->current_line->last_cursor_pos = 0;
                buffer->max_cursor_pos = 0;
            } else {
                buffer->current_line->last_cursor_pos += offset;
                buffer->max_cursor_pos = buffer->current_line->last_cursor_pos;
            }

        } else if (offset > 0) {
            if (buffer->current_line->last_cursor_pos + offset>= (int)strlen(buffer->current_line->text)) {
                buffer->current_line->last_cursor_pos = strlen(buffer->current_line->text);
            } else {
                buffer->current_line->last_cursor_pos += offset;
                buffer->max_cursor_pos = buffer->current_line->last_cursor_pos;
            }
        }

        snap_cursor(buffer);
        buffer->needs_to_render = 1;
    }
}

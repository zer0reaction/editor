// Moving cursor aroung, inserting text, etc

#pragma once

#include "defines.h"
#include "buffer_operations.h"

void snap_cursor(text_buffer* buffer);
void move_cursor_vertically(text_buffer* buffer, int offset);

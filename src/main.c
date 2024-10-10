#include "raylib.h"
#include "file_operations.h"
#include "buffer_operations.h"
#include "display_operations.h"
#include "defines.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    text_buffer* buff = create_buffer();
    char* text = get_file_text(argv[1]);
    put_text_in_buffer(buff, text);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "editor");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);

    init_display("/usr/share/fonts/TTF/Hack-Regular.ttf");

    int last_width = GetScreenWidth();
    int last_height = GetScreenWidth();

    while(!WindowShouldClose()) {
        BeginDrawing();

        // If the window is resized
        if (last_width != GetScreenWidth() || last_height != GetScreenHeight())
            buff->needs_to_render = 1;

        if (buff->needs_to_render) {
            display_buffer(buff, 0, 0);
            buff->needs_to_render = 0;
        }

        EndDrawing();
    }

    end_display();
    free_buffer(buff);
    CloseWindow();
    return 0;
}

#include "raylib.h"
#include "file_operations.h"
#include "buffer_operations.h"
#include "display_operations.h"
#include "cursor_operations.h"
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
    int last_height = GetScreenHeight();

    long long int frame = 0;

    while(!WindowShouldClose()) {
        BeginDrawing();

        if (IsKeyPressed(KEY_J)) 
            move_cursor_vertically(buff, -1);
        if (IsKeyPressed(KEY_K)) 
            move_cursor_vertically(buff, 1);

        // If the window is resized
        if (last_width != GetScreenWidth() || last_height != GetScreenHeight()) {
            buff->needs_to_render = 1;
        }

        if (buff->needs_to_render) {
            printf("%s Frame: %lli\n", "Rendering buffer", frame);
            display_buffer(buff);
            buff->needs_to_render = 0;
        }

        last_width = GetScreenWidth();
        last_height = GetScreenHeight();
        EndDrawing();
        frame++;
    }

    end_display();
    free_buffer(buff);
    CloseWindow();
    return 0;
}

#include "raylib.h"
#include "file_operations.h"
#include "buffer_operations.h"
#include "display_operations.h"

#include <stdio.h>
#include <stdlib.h>

#define FONT_SIZE 20
#define FONT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int main(int argc, char** argv) {
    struct text_buffer* buff = (struct text_buffer*)malloc(sizeof(struct text_buffer));
    buff->first_line = NULL;

    char* text = get_file_text(argv[1]);

    Color font_color = FONT_COLOR;
    Color background_color = BACKGROUND_COLOR;

    put_text_in_buffer(buff, text);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "editor");
    SetTargetFPS(60);

    int show = 0;

    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) show = 1;
        else show = 0;

        if (show)
            display_buffer(buff, FONT_SIZE, &font_color, &background_color, 0, 0);
        else {
            BeginDrawing();
            EndDrawing();
        }
    }

    CloseWindow();
    free_buffer(buff);
    return 0;
}

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FONT_SIZE 20
#define FONT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

struct text_line {
    int line_number;
    char* line_number_text;
    char* text;
};

struct text_buffer {
    int lines_count;
    struct text_line* lines;
};


void close_window(Font* font) {
    UnloadFont(*font); // is this enough?
    CloseWindow();
}


void display_line(struct text_line* line, Font* font, int y) {
    int current_x = 0;

    DrawTextEx(*font, line->line_number_text, (Vector2){ current_x, y }, (float)FONT_SIZE, 0.0f, FONT_COLOR);
    current_x += FONT_SIZE * strlen(line->line_number_text) / 2.0;
    DrawTextEx(*font, line->text, (Vector2){current_x, y}, (float)FONT_SIZE, 0.0f, FONT_COLOR);
}


void display_buffer(struct text_buffer* buf, Font* font) {
    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < buf->lines_count; i++) {
        display_line(&(buf->lines[i]), font, i * FONT_SIZE);
    }

    EndDrawing();
}


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "editor");
    SetTargetFPS(60);

    Font font = LoadFontEx("./resources/fonts/0xproto.ttf", 20, 0, 0);

    struct text_buffer buf;
    struct text_line lines[1];

    char test_text[100] = "test text\0";

    lines[0].text = test_text;
    lines[0].line_number = 1;
    lines[0].line_number_text = "1 | ";
    
    buf.lines = lines;
    buf.lines_count = 1;


    while (!WindowShouldClose()) {
        display_buffer(&buf, &font);
    }

    close_window(&font);
    return 0;
}

#include "raylib.h"
#include "file_operations.h"
#include "text_operations.h"

#include <stdio.h>
#include <stdlib.h>

#define FONT_SIZE 20
#define FONT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

int main(int argc, char** argv) {
    struct text_buffer buff;
    buff.first_line = NULL;

    char* text = get_file_text("/home/zer0/git/editor/src/main.c");

    put_text_in_buffer(&buff, text);
    print_buffer_text(&buff);

    return 0;
}

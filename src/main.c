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
    char text[100] = "kek\nkek";

    put_text_in_buffer(&buff, text);
    return 0;
}

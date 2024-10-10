#include "raylib.h"
#include "file_operations.h"
#include "buffer_operations.h"

#include <stdio.h>
#include <stdlib.h>

#define FONT_SIZE 20
#define FONT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

int main(int argc, char** argv) {
    struct text_buffer* buff = (struct text_buffer*)malloc(sizeof(struct text_buffer));
    buff->first_line = NULL;

    char* text = get_file_text(argv[1]);

    put_text_in_buffer(buff, text);
    print_buffer_text(buff);
    free_buffer(buff);

    return 0;
}

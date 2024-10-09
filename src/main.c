#include "raylib.h"
#include "file_operations.h"

#include <stdio.h>
#include <stdlib.h>

#define FONT_SIZE 20
#define FONT_COLOR WHITE
#define BACKGROUND_COLOR BLACK

int main(int argc, char** argv) {
    s8* text = get_text("/home/zer0/test.txt");
    printf("%s", text);

    free(text);
    return 0;
}

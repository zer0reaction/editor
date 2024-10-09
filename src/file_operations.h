#pragma once
#include "defines.h"

u8 check_file_existence(const char* path);
u64 get_file_size(const char* path);
s8* get_text(const char* path);

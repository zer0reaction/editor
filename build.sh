#!/bin/bash

mkdir -p bin

assembly="editor"

sourceFlags="src/*.c"
assemblyFlags="-o bin/$assembly"
includeFlags="-Iinclude/raylib"
libraryFlags="-Llib/raylib -l:libraylib.a -lm"
warningFlags="-Wall -Werror"
# warningFlags=""


gcc $warningFlags $sourceFlags $assemblyFlags $includeFlags $libraryFlags
# ./bin/$assembly

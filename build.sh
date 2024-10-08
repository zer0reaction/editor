#!/bin/bash

mkdir -p bin

assembly="editor"

sourceFlags="src/*.c"
assemblyFlags="-o bin/$assembly"
includeFlags="-Iinclude/raylib"
libraryFlags="-Llib -lraylib"
# warningFlags="-Wall -Werror"
warningFlags=""


g++ $warningFlags $sourceFlags $assemblyFlags $includeFlags $libraryFlags
# ./bin/$assembly

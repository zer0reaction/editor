#!/bin/bash

mkdir -p bin

assembly="editor"

sourceFlags="src/*.c"
assemblyFlags="-o bin/$assembly"

includeFlags="-Iinclude/raylib"
libraryFlags="-Llib -lraylib"


g++ $sourceFlags $assemblyFlags $includeFlags $libraryFlags
./bin/$assembly

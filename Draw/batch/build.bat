@echo off
@REM gcc version 4.8.3 (GCC) 
cd ../
g++ -std=c++11  -g -pthread "main.cpp" "src/Window.cpp" "src/Draw.cpp" "src/Entity.cpp" -o "bin/Debug/main.exe" -pedantic -Wall -Wextra -lmingw32 -lSDL2main -lSDL2
cd batch/
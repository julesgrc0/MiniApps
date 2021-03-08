@echo off
cd ../
g++  -std=gnu++11 -std=c++11 -g -pthread -static-libgcc -static-libstdc++  "main.cpp" "src/Window.cpp" "src/Draw.cpp" "src/Entity.cpp" -o "bin/Release/main.exe" -lmingw32 -lSDL2main -lSDL2
cd batch/
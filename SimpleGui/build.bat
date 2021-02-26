@echo off
cd C:\Win-builds\mingw64\bin
g++ -g -std=c++0x -pthread "C:\Users\jules\OneDrive\Bureau\SDL\main.cpp" "C:\Users\jules\OneDrive\Bureau\SDL\src\*.cpp" -o "C:\Users\jules\OneDrive\Bureau\SDL\bin\main" -Wall  -I "C:\Users\jules\OneDrive\Bureau\SDL\include" -L "C:\Users\jules\OneDrive\Bureau\SDL\lib" -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2 && cd "C:\Users\jules\OneDrive\Bureau\SDL\"
cd C:\Users\jules\OneDrive\Bureau\SDL\
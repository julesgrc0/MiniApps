
cd C:\Win-builds\mingw64\bin
@REM -g  -std=c++0x -pthread
g++  "C:\APPS\run\Mini-Apps\SimpleGui\main.cpp" "C:\APPS\run\Mini-Apps\SimpleGui\src\*.cpp" -o "C:\APPS\run\Mini-Apps\SimpleGui\bin\main" -Wall  -I "C:\APPS\run\Mini-Apps\SimpleGui\include" -L "C:\APPS\run\Mini-Apps\SimpleGui\lib" -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2 && cd "C:\APPS\run\Mini-Apps\SimpleGui"
cd C:\APPS\run\Mini-Apps\SimpleGui
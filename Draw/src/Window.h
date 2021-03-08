#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include "Utils.h"
#include "Draw.h"
#include "Entity.h"

class GameWindow
{
public:
    GameWindow(const char *, Size);
    ~GameWindow();
    bool Run();

private:
    void Update();
    void Draw();
    void Event();
    void Color(int, int, int);
    void Drawline(int x0, int y0, int x1, int y1);
    void Render();

    SDL_Window *window;
    SDL_Renderer *renderer;
    GameDraw *draw;
    bool isRunning;
    bool isDown;
    Point last;
    int points[400][600];
    int CircleSize = 10;
    std::string title;
    std::vector<std::pair<Entity, Rgb> > entities;
};
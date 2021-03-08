#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Utils.h"

class GameDraw
{
public:
    GameDraw(SDL_Renderer *);
    ~GameDraw();
    bool DrawImage(const char *, Point, Size);
    void DrawPixel(Point);

private:
    int isInLoadImages(const char*);

    SDL_Renderer *renderer;
    std::vector< std::pair<std::string,SDL_Surface*> > Images;    
};

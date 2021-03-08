#include <iostream>
#include <SDL2/SDL.h>
#include "Draw.h"
#include "Utils.h"

GameDraw::GameDraw(SDL_Renderer *render)
{
    this->renderer = render;
}

int GameDraw::isInLoadImages(const char *path)
{
    if(this->Images.size() == 0)
    {
        return -1;
    }

    for (int i = 0; i < (int)this->Images.size(); i++)
    {
        if (this->Images[i].first == path)
        {
            return i;
        }
    }

    return -1;
}

void GameDraw::DrawPixel(Point pos)
{
    SDL_RenderDrawPoint(this->renderer, pos.x, pos.y);
}

bool GameDraw::DrawImage(const char *path, Point pos, Size size)
{
    SDL_Surface *image;
    SDL_Texture *texture;
    int index = this->isInLoadImages(path);

    if (index != -1)
    {
        image = this->Images[index].second;
    }
    else
    {
        image = SDL_LoadBMP(path);
        std::pair<std::string, SDL_Surface *> save(path, image);
        this->Images.push_back(save);
    }

    if (!image)
    {
        return false;
    }

    texture = SDL_CreateTextureFromSurface(this->renderer, image);

    if (!texture)
    {
        return false;
    }
    SDL_FreeSurface(image);

    SDL_Rect rect = {pos.x, pos.y, size.width, size.height};
    if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h))
    {
        return false;
    }
    if (SDL_RenderCopy(this->renderer, texture, NULL, &rect))
    {
        return false;
    }
    SDL_DestroyTexture(texture);

    return true;
}

GameDraw::~GameDraw()
{
    this->Images.clear();
}
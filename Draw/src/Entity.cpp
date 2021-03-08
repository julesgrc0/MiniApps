#include <iostream>
#include <SDL2/SDL.h>
#include "Utils.h"
#include "Draw.h"
#include "Entity.h"

Entity::Entity(Point pos, int r)
{
    this->pos = pos;
    this->r = r;
}

void Entity::DrawCircle(GameDraw *draw, int xc, int yc, int x, int y)
{
    Point pos[8] = {{xc + x, yc + y},
                    {xc - x, yc + y},
                    {xc + x, yc - y},
                    {xc - x, yc - y},
                    {xc + y, yc + x},
                    {xc - y, yc + x},
                    {xc + y, yc - x},
                    {xc - y, yc - x}};

    for (int i = 0; i < 8; i++)
    {
        draw->DrawPixel(pos[i]);
    }
}

void Entity::Draw(GameDraw *draw)
{
    int x = 0, y = this->r;
    int d = 3 - 2 * this->r;

    int xc = this->pos.x;
    int yc = this->pos.y;
    this->DrawCircle(draw, xc, yc, x, y);

    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
        {
            d = d + 4 * x + 6;
        }
        this->DrawCircle(draw, xc, yc, x, y);
    }
}

void Entity::SetPoint(Point pos)
{
    this->pos = pos;
}

Point Entity::GetPoint()
{
    return this->pos;
}

Entity::~Entity() {}
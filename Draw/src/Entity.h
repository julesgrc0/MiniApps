#pragma once
#include <iostream>
#include "Utils.h"
#include "Draw.h"

class Entity
{
public:
    Entity(Point, int);
    ~Entity();
    void Draw(GameDraw *);
    void SetPoint(Point);
    Point GetPoint();
private:
    void DrawCircle(GameDraw *, int, int, int, int);
    Point pos;
    int r;
};

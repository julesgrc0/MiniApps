#pragma once

#ifndef _DRAW_
#define _DRAW_

#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include "utils.h"

class Draw 
{
    public:
        Draw(SDL_Renderer* render);
        void Update(void(*Draw)(Draw rnd));
        void DrawGraphe(std::vector<Point> points,Rgb color);
        void DrawGraphe(Point pos,std::vector<Point> points,Rgb color);
        void DrawShape(std::vector<Point> points,Rgb color);
        void DrawImage(std::string path,Item item);
        void Line(Point start,Point end);
        void Arc(Point start,Point end,int h);
        Size Text(std::string text,int fontSize,Item item);
        Size GetTextSize(std::string text,int fontSize);
        void Color(Rgb color,Uint8 opacity);
        void Clear();
        void Present();
        void Rect(Point pos,Size size);
    private:
        SDL_Renderer* render;
};

#endif // !_DRAW_
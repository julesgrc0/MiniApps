#pragma once

#ifndef _UTILS_
#define _UTILS_
#include<SDL2/SDL.h>
#include<iostream>
#include <cstdarg>

#define DEBUG

typedef struct Point
{
    int x,y;
}Point;

typedef struct Rgb
{
    Uint8 r,g,b;
}Rgb;


typedef struct Item
{
    int x,y;
    int w,h;
    Uint8  opacity;
    Rgb color;
}Item;

typedef struct Size{
    int w,h;
}Size;

#define NULL_COLOR (Rgb){0,0,0}

void Debug(std::string str,std::string info="");

#endif // !_UTILS_
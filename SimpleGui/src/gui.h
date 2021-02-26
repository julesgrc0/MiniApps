#pragma once

#ifndef _GUI_
#define _GUI_
#include<SDL2/SDL.h>
#include <iostream>
#include "draw.h"
#include "utils.h"

typedef enum GuiTypes{
    BUTTON,
    BLOCK,
    HEADER
}GuiTypes;

typedef struct GuiItem{
    int x,y;
    int w,h;
    GuiTypes type;
    int id;
}GuiItem;

class Gui
{
    public:
        Gui(Draw *rnd);
        GuiItem Button(std::string content,Item item,bool hover);
        GuiItem Block(Point pos,Size size,bool ligth);
        GuiItem TextContent(std::string content,Point pos,int with);
        GuiItem Matrix(int** matrix,int length,Point pos,int size);
        bool isHover(Point mouse,GuiItem item);
    private:
        int id;
        Draw* rnd;
};

#endif // !_GUI_
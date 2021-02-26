#include "gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "draw.h"
#include "utils.h"
#include "const.h"
#include <math.h>
#include<string>

Gui::Gui(Draw *rnd)
{
    this->rnd = rnd;
}

GuiItem Gui::Button(std::string content, Item item, bool hover = false)
{
    this->id++;
    int padding = 5;
    Size textSize = this->rnd->GetTextSize(content, 12);
    int x = item.x;
    int y = item.y;
    int w = textSize.w + padding * 2;
    int h = textSize.h + padding * 2;
    Rgb color = {145, 145, 145};
    Rgb bk = {212, 212, 212};

    if (hover)
    {
        color = {128, 128, 128};
        bk = {171, 171, 171};
    }

    Point pos = {x, y};
    Size size = {w, h};
    this->rnd->Color(bk, item.opacity);
    this->rnd->Rect(pos, size);

    this->rnd->Color(color, item.opacity);

    this->rnd->Line({x, y}, {x + w, y});
    this->rnd->Line({x, y + h}, {x + w, y + h});
    this->rnd->Line({x, y}, {x, y + h});
    this->rnd->Line({x + w, y}, {x + w, y + h});

    Item it = {(item.x + w) - (textSize.w + padding), (item.y + h) - (textSize.h + padding), 0, 0, item.opacity, {0, 0, 0}};
    this->rnd->Text(content, 12, it);

    GuiItem guiItem = {x, y, w, h, BUTTON, this->id};
    return guiItem;
}

GuiItem Gui::Block(Point pos, Size size, bool ligth)
{
    this->id++;
    Rgb color = {227, 227, 227};
    if (ligth)
    {
        color = {207, 207, 207};
    }
    this->rnd->Color(color, SDL_ALPHA_OPAQUE);
    this->rnd->Rect(pos, size);

    int x = pos.x;
    int y = pos.y;
    int w = size.w;
    int h = size.h;
    color = {102, 102, 102};
    this->rnd->Color(color, SDL_ALPHA_OPAQUE);

    this->rnd->Line({x, y}, {x + w, y});
    this->rnd->Line({x, y + h}, {x + w, y + h});
    this->rnd->Line({x, y}, {x, y + h});
    this->rnd->Line({x + w, y}, {x + w, y + h});
    GuiItem guiItem = {x, y, w, h, BLOCK, this->id};
    return guiItem;
}

bool Gui::isHover(Point mouse, GuiItem item)
{
    if (mouse.x >= item.x && mouse.y >= item.y)
    {
        if (mouse.x <= (item.x + item.w) && mouse.y <= (item.y + item.h))
        {
            return true;
        }
    }
    return false;
}

GuiItem Gui::TextContent(std::string content, Point pos, int width)
{
    this->id++;
    int textSize = content.size();
    Size s = this->rnd->GetTextSize(content, 12);
    int w = s.w;
    int h = s.h;
    int charPixel = ceil((double)w / textSize);
    int line = width / charPixel;

    std::string text = "";
    int l = 0;
    int i;
    for (i = 0; i < ceil((double)textSize / line); i++)
    {
        for (int j = 0; j < line; j++)
        {
            text += content[l];
            l++;
        }
        Item it = {pos.x, pos.y + ((i)*h), 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR};
        if (i == 1)
        {
            it = {pos.x, pos.y + h, 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR};
        }

        this->rnd->Text(text, 12, it);
        text = "";
    }
    GuiItem guiItem = {pos.x, pos.y, width, (i * h), BLOCK, this->id};
    return guiItem;
}

GuiItem Gui::Matrix(int **matrix,int length, Point pos, int size)
{
    this->id++;
    this->rnd->Color({92, 92, 92}, SDL_ALPHA_OPAQUE);
    int x = pos.x;
    int y = pos.y;
    int sep = length;
    int caseV = ceil((double)(size / sep));
    for (int i = y; i <= y + size; i += caseV)
    {
        this->rnd->Line({x, i}, {x + size, i});
    }
    for (int j = x; j <= x + size; j+= caseV)
    {
        this->rnd->Line({j, y}, {j, y+size});
    }
    for(int line=0;line<length;line++)
    {
        for(int col=0;col<length;col++)
        {
            std::string content = std::to_string(matrix[line][col]);
            int mX  = ((caseV/2) - (this->rnd->GetTextSize(content,10).w/2));
            int mY = ((caseV/2) - (this->rnd->GetTextSize(content,10).h/2));
            int itX = pos.x + caseV * line + mX;
            int itY = pos.y + caseV * col + mY;
            Item mIt = {
                itX,
                itY,
                0,
                0,
                SDL_ALPHA_OPAQUE,
                NULL_COLOR
            };
            this->rnd->Text(content,10,mIt);
        }
    }
    GuiItem guiItem = {pos.x, pos.y, size, size, BLOCK, this->id};
    return guiItem;
}

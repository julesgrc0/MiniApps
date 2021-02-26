#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include "utils.h"
#include "draw.h"
#include "const.h"

Draw::Draw(SDL_Renderer* render)
{
    this->render = render;
}

void Draw::Update(void(*Draw)(Draw rnd))
{
    SDL_SetRenderDrawColor(this->render,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->render);
    Draw(*this);
    SDL_RenderPresent(this->render);
}

void Draw::DrawImage(std::string path,Item item)
{
    SDL_SetRenderDrawColor(this->render,item.color.r,item.color.g,item.color.b,item.opacity);
    SDL_Surface *image = SDL_LoadBMP(path.c_str());
    SDL_Texture *texture;
    SDL_Rect rect = {item.x, item.y, item.w, item.h};
    
    if (!image)
    {
        Debug("[ERROR] Fail to load image: ", SDL_GetError());
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(render, image);

    if (!texture)
    {
        Debug("[ERROR] Fail to create texture: ", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(image);

    if (SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h))
    {
        Debug("[ERROR] Fail to query texture: ", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderCopy(render, texture, NULL, &rect))
    {
        Debug("[ERROR] Fail to create render texture: ", SDL_GetError());
        exit(1);
    }
    SDL_DestroyTexture(texture);
}

void Draw::DrawShape(std::vector<Point> points,Rgb color)
{
    SDL_SetRenderDrawColor(this->render,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
    for(Point point : points)
    {
        SDL_RenderDrawPoint(this->render,point.x,point.y);
    }
}

Size Draw::Text(std::string text,int fontSize,Item item)
{
    SDL_Texture *texture;
    SDL_Surface *surface;
    TTF_Font *font = TTF_OpenFont(DEFAULT_FONT, fontSize);
    SDL_Rect block = {item.x,item.y,0,0};
    SDL_Color textColor = {item.color.r,item.color.g,item.color.b, item.opacity};

    if(!font)
    {
        Debug("[ERROR] Fail to load font: ",SDL_GetError());
        exit(1);
    }
    surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if(!surface)
    {
        Debug("[ERROR] Fail to render surface: ",SDL_GetError());
        exit(1);
    }
    texture = SDL_CreateTextureFromSurface(this->render, surface);
    if(!texture)
    {
        Debug("[ERROR] Fail to create texture: ",SDL_GetError());
        exit(1);
    }

    if (SDL_QueryTexture(texture, NULL, NULL, &block.w, &block.h))
    {
        Debug("[ERROR] Fail to query texture: ", SDL_GetError());
        exit(1);
    }
    if (SDL_RenderCopy(render, texture, NULL, &block))
    {
        Debug("[ERROR] Fail to create render texture: ", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    int w,h;
    TTF_SizeText(font,text.c_str(),&w,&h);
    Size size = {w,h};
    return size;
}

void Draw::DrawGraphe(std::vector<Point> points,Rgb color)
{
    SDL_SetRenderDrawColor(this->render,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
    Point lastPoint;
    bool firstLoop = true;
    for(Point point : points)
    {
        if(!firstLoop)
        {
            SDL_RenderDrawLine(this->render,lastPoint.x,lastPoint.y,point.x,point.y);
            lastPoint = point;
        }else{
            firstLoop = false;
            lastPoint = point;
        }
    }
}

void Draw:: DrawGraphe(Point pos,std::vector<Point> points,Rgb color)
{
    SDL_SetRenderDrawColor(this->render,color.r,color.g,color.b,SDL_ALPHA_OPAQUE);
    Point lastPoint;
    bool firstLoop = true;
    for(Point point : points)
    {
        if(!firstLoop)
        {
            SDL_RenderDrawLine(this->render,lastPoint.x+pos.x,lastPoint.y+pos.y,point.x+pos.x,point.y+pos.y);
            lastPoint = point;
        }else{
            firstLoop = false;
            lastPoint = point;
        }
    }
}

void Draw::Line(Point start,Point end)
{
    SDL_RenderDrawLine(this->render,start.x,start.y,end.x,end.y);
}

void Draw::Color(Rgb color,Uint8 opacity)
{
    SDL_SetRenderDrawColor(this->render,color.r,color.g,color.b,opacity);
}

void Draw::Clear()
{
    SDL_SetRenderDrawColor(this->render,0,0,0,SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->render);
}

void Draw::Present()
{
    SDL_RenderPresent(this->render);
}

void Draw::Rect(Point pos,Size size)
{
    SDL_Rect r = {pos.x,pos.y,size.w,size.h};
    SDL_RenderFillRect(this->render,&r);
}

Size Draw::GetTextSize(std::string text,int fontSize)
{
    TTF_Font *font = TTF_OpenFont(DEFAULT_FONT, fontSize);
    int w,h;
    TTF_SizeText(font,text.c_str(),&w,&h);
    Size size = {w,h};
    return size;
}

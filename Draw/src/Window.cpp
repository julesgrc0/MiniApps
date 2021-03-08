#include <iostream>
#include <SDL2/SDL.h>
#include <thread>
#include "Window.h"
#include "Entity.h"

GameWindow::GameWindow(const char *title, Size size)
{
    this->isRunning = false;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.width, size.height, 0);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
    this->draw = new GameDraw(this->renderer);
    this->title = std::string(title);
}

bool GameWindow::Run()
{
    if (!this->isRunning)
    {
        this->isRunning = true;

        int start = SDL_GetTicks();
        int frames = 0;
        this->Update();

        while (this->isRunning)
        {
            frames++;
            int current = SDL_GetTicks();
            if (current - start > 1000)
            {
                SDL_SetWindowTitle(this->window, (this->title + " - FPS: " + std::to_string(frames)).c_str());
                start = current;
                frames = 0;
            }
            this->Event();
        }
        return true;
    }
    return false;
}

void Export(const char *title, int points[400][600])
{
    FILE *file = fopen(title, "w+");

    if (file != NULL)
    {
        for (int i = 0; i < 400; i++)
        {
            std::string line;
            for (int j = 0; j < 600; j++)
            {
                line += std::to_string(points[i][j]);
            }
            fputs((line + "\n").c_str(), file);
        }

        fclose(file);
    }
}

void GameWindow::Render()
{
    SDL_RenderPresent(this->renderer);
}

void GameWindow::Drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;

    dx = x1 - x0;
    dy = y1 - y0;

    x = x0;
    y = y0;

    p = 2 * dy - dx;
    this->Color(255, 0, 0);

    while (x < x1)
    {
        if (p >= 0)
        {
            if (y > 0 && y < 400 && x > 0 && x < 600)
            {
                SDL_RenderDrawPoint(this->renderer, x, y);
            }
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
        else
        {
            if (y > 0 && y < 400 && x > 0 && x < 600)
            {
                SDL_RenderDrawPoint(this->renderer, x, y);
            }
            p = p + 2 * dy;
        }
        this->Render();
        x = x + 1;
    }
}

void GameWindow::Event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (this->isDown)
        {
            int x = event.button.x, y = event.button.y;
            if (y > 0 && y < 400 && x > 0 && x < 600)
            {
                SDL_RenderDrawPoint(this->renderer, x, y);
                SDL_RenderPresent(this->renderer);
                this->points[y][x] = 1;
            }
            this->last = {x, y};
        }

        switch (event.type)
        {
        case SDL_QUIT:
            this->isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->isDown = true;
            break;
        case SDL_MOUSEBUTTONUP:
            this->isDown = false;
            break;
        case SDL_KEYDOWN:
        {
            SDL_Keycode key = event.key.keysym.sym;
            switch (key)
            {
            case SDLK_p:
            {
                std::thread t1(Export, (this->title + ".txt").c_str(), this->points);
                t1.join();
            }
            break;
            case SDLK_c:
            {
                Entity circle = Entity(last, this->CircleSize);
                circle.Draw(this->draw);
                SDL_RenderPresent(this->renderer);
            }
            break;
            case SDLK_1:
                this->CircleSize--;
                break;
            case SDLK_2:
                this->CircleSize++;
                break;
            }
        }
        break;
        }
    }
}

void GameWindow::Update()
{
    this->Color(0, 0, 0);
    SDL_RenderClear(this->renderer);
    this->Draw();
    SDL_RenderPresent(this->renderer);
}

void GameWindow::Draw()
{
    this->Color(5, 46, 28);
}

void GameWindow::Color(int red, int green, int blue)
{
    SDL_SetRenderDrawColor(this->renderer, red, green, blue, SDL_ALPHA_OPAQUE);
}

GameWindow::~GameWindow()
{
    this->isRunning = false;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
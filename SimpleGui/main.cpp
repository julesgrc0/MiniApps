#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include <iostream>
#include "src/utils.h"
#include "src/draw.h"
#include "src/const.h"
#include "src/gui.h"

void DrawMain(Gui g, Draw rnd);
void Init(Gui g);
void Hover(Gui g);
void Click(Gui g);
int** createMatrix(int size);
int** actualMatrix;
int acutalMatrixLength=0;
SDL_Renderer *render;

Point mouse = {0, 0};
Point click = {-1,-1};

int main(int argc, char *argv[])
{
    // #include <unistd.h>
    // char cwd[PATH_MAX];
    // getcwd(cwd, sizeof(cwd));
    // std::cout << cwd << std::endl;

    bool Run = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Debug("Fail to init", SDL_GetError());
    }
    if (TTF_Init() != 0)
    {
        Debug("Fail to init SDL", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_RenderPresent(render);
    Draw rnd = Draw(render);
    Gui g = Gui(&rnd);

    Init(g);
    rnd.Clear();
    DrawMain(g, rnd);
    rnd.Present();

    while (Run)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                Run = false;
                break;
            case SDL_MOUSEMOTION:
                Hover(g);
                mouse = {event.button.x, event.button.y};
                break;
            case SDL_MOUSEBUTTONDOWN:
                Click(g);
                click = {event.button.x, event.button.y};
                break;
            }
        }
    }

    Debug("Quit window");
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

GuiItem clear_BTN,removelast_BTN;

void Init(Gui g)
{
    clear_BTN = g.Button("clear matrix", {30, 85, 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR},false);
    removelast_BTN = g.Button("remove last", {30, 115, 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR},false);
    actualMatrix = createMatrix(5);
    acutalMatrixLength = 5;
}

void DrawMain(Gui g, Draw rnd)
{
    g.Block({0,0},{200,WINDOW_HEIGHT},false);
    
    g.Block({20,20},{160,50},true);
    g.TextContent("Graphe editor with a real time matrix render.",{25,25},150);
    
    g.Block({20,80},{160,100},true);
    Hover(g);

    g.Block({20,190},{160,160},true);
    g.Matrix(actualMatrix,acutalMatrixLength,{20,190},160);
}

void Hover(Gui g)
{
    g.Button("clear matrix", {30, 85, 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR}, g.isHover(mouse, clear_BTN));
    g.Button("remove last", {30, 115, 0, 0, SDL_ALPHA_OPAQUE, NULL_COLOR},g.isHover(mouse, removelast_BTN));
    g.Block({20,190},{160,160},true);
}

void Click(Gui g)
{
    if(click.x>0)
    {
        if(g.isHover(click, clear_BTN))
        {
            std::cout << "Btn click !!!" << std::endl;
        }
        click = {-1,-1};
    }
}

int** createMatrix(int size)
{
    int rows = size,cols = size;
    int** matrix = new int*[rows];
    if (rows)
    {
        matrix[0] = new int[rows * cols];
        for (int i = 1; i < rows; ++i)
        {
            matrix[i] = matrix[0];
            for(int j=0;j<cols;j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

// rnd.Update([](Draw rnd) {
//     std::vector<Point> points =
//     {
//         (Point){0, 0},
//         (Point){3, 10},
//         (Point){5, 20},
//         (Point){10, 20},
//         (Point){15, 90},
//         (Point){20, -10},
//         (Point){23, -100},
//         (Point){40, 10},
//         (Point){100, 0},
//         (Point){150, 10},
//         (Point){200, 20},
//         (Point){345, 20},
//         (Point){500, 90},
//         (Point){630, -10},
//         (Point){670, -100},
//         (Point){683, 10},
//     };
//     rnd.DrawGraphe((Point){100,100},points, (Rgb){50, 168, 82});
// });
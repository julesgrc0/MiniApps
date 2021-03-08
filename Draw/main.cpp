#define SDL_MAIN_HANDLED

#include<iostream>
#include<SDL2/SDL.h>
#include "src/Window.h"
#include "src/Utils.h"

int main(int argc,char** argv)
{
	Size windowSize = {600,400};
	GameWindow game = GameWindow("Game",windowSize);
	game.Run();
	return 0;
}

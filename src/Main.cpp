#include <iostream>

#include "SDL2/SDL.h"

#include "Core/Window.h"

// TODO:
// Get OpenGL up and running
// Get on clearing screen, drawing something simple and then setup a proper window
// Event handeling
// Make sure I can compile on linux aswell
// FUCKING PROFIT

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	ce::Window window("Hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);

	bool running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
		}
	}

	SDL_Quit();

	return 0;
}
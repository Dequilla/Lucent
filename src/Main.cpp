#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "Core/Window.h"

// TODO:
// Get OpenGL up and running
// Get on clearing screen, drawing something simple and then setup a proper window
// Event handeling
// Make sure I can compile on linux aswell
// FUCKING PROFIT

int main(int argc, char* argv[])
{
	ce::Window window("Hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
	window.setClearColor(0.f, 0.f, 0.f);

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

		window.clear();

		window.display();
	}

	SDL_Quit();

	return 0;
}
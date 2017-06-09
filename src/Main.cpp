#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "Core/Window.h"

#include "Core/GameMode.h"

// TODO: KEEP GOING ON INPUT


int main(int argc, char* argv[])
{
	ce::Window window(
		"Hello world", 
		ce::WINDOWPOS_CENTERED, 
		ce::WINDOWPOS_CENTERED,
		800, 600, 
		ce::WINDOW_RESIZABLE
	);
	window.setClearColor(0.f, 0.f, 0.f);

	ce::GameMode mode;

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
			mode.checkInput(e); // TODO
		}

		window.clear();

		window.display();
	}

	SDL_Quit();

	return 0;
}
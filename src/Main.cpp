#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "Core/Window.h"
#include "Core/GameMode.h"
#include "Core/Application.h"

int main(int argc, char* argv[])
{
	ce::core::Application::getInstance().init();
	
	ce::core::Window window(
		"Hello world", 
		ce::core::WINDOWPOS_CENTERED,
		ce::core::WINDOWPOS_CENTERED,
		800, 600, 
		ce::core::WINDOW_RESIZABLE
	);
	window.setClearColor(0.f, 0.f, 0.f);

	window.setWindowFlags(ce::core::WINDOW_SHOWN);

	ce::core::GameMode mode;

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
			mode.checkInput(e);
		}

		window.clear();

		window.display();
	}

	SDL_Quit();

	return 0;
}
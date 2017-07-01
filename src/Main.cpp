#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "GLM/glm.hpp"

#include "Core/Time.h"
#include "Core/Window.h"
#include "Core/Application.h"

#include "Game/GameMode/ExampleGameMode.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

bool fullscreen = false;

// Also in CMakeLists.txt
// TODO: on WIN32 copy dlls into build directories Debug and Release
// TODO: Create build scripts ? Windows and linux(ubuntu) makes testing the engine faster even if just a few minutes faster
// TODO TODO TODO TODO
// TODO TODO TODO TODO
// TODO TODO TODO TODO
// TODO TODO TODO TODO

#include "Core/Utility/log.h"

int main(int argc, char* argv[])
{
	ce::core::Application::init();
	ce::core::Application::setScreenBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	ce::core::Window window(
		"Hello world",
		ce::core::WINDOWPOS_CENTERED,
		ce::core::WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		ce::core::WINDOW_RESIZABLE
	);

	window.setWindowGrab(true);

	ce::game::ExampleGameMode exGameMode;
	exGameMode.init();

	//renderer.setScreenBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	ce::core::Clock clock;
	clock.start();

	bool running = true;
	while (running)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			exGameMode.checkInput(e);

			if (e.type == SDL_QUIT)
			{
				running = false;
			}

			if (e.type == SDL_KEYDOWN)
			{
				// TOGGLE FULLSCREEN
				if (e.key.keysym.sym == SDLK_F11)
				{
					if (fullscreen == false)
					{
						window.setWindowFullscreen(ce::core::WINDOW_FULLSCREEN_DESKTOP);
						glViewport(0, 0, window.getSize().x, window.getSize().y);
						fullscreen = true;
					}
					else
					{
						window.setWindowFullscreen(0);
						glViewport(0, 0, window.getSize().x, window.getSize().y);
						fullscreen = false;
					}
				}
			}
		}

		window.clear();
		glClear(GL_DEPTH_BUFFER_BIT);

		exGameMode.begin();
		exGameMode.tick(clock.restart().asSeconds());
		exGameMode.draw();
		exGameMode.end();

		window.display();
	}

	SDL_Quit();

	return 0;
}

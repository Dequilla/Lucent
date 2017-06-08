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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize SDL with error:\n" << SDL_GetError() << std::endl;
		return -1;
	}

	ce::Window window("Hello world", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600);
	
	// Set openGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create GL context
	SDL_GLContext glContext = SDL_GL_CreateContext(window.getSDLWindow());
	if (glContext == NULL)
	{
		std::cout << "Failed to create a GL context for the window with error:\n" << SDL_GetError() << std::endl;

		return -1;
	}

	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

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

		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(window.getSDLWindow());
	}

	SDL_GL_DeleteContext(glContext);
	SDL_Quit();

	return 0;
}
#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "GLM/glm.hpp"

#include "Graphics/Text/Font.h"

#include "Core/Time.h"
#include "Core/Window.h"
#include "Core/Application.h"

#include "Game/GameMode/ExampleGameMode.h"

#include "Graphics/Text/Font.h"
#include "Graphics/Text/Text.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

bool fullscreen = false;

// TODO: on WIN32 copy dlls into build directories Debug and Release

#include "Core/Utility/log.h"

int main(int argc, char* argv[])
{
	ce::core::Application::init();
	ce::core::Application::setScreenBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	ce::core::Application::getInstance().maxDirLights = 1;
	ce::core::Application::getInstance().maxPointLights = 10;
	ce::core::Application::getInstance().maxSpotLights = 1;

	ce::core::Window window(
		"Hello world",
		ce::core::WINDOWPOS_CENTERED,
		ce::core::WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		ce::core::WINDOW_RESIZABLE
	);

	ce::core::Application::enableVSYNC(true);

	window.setWindowGrab(true);

	ce::game::ExampleGameMode exGameMode;
	exGameMode.init();

	glEnable(GL_DEPTH_TEST);

	ce::core::Clock clock;
	clock.start();

	// FPS -- TEMP, gonna do better
	bool showFPS = false;
	float frameCount = 1.0f;
	ce::graphics::Font font;
	font.load("Resources/Fonts/MotionControl-Bold.otf");
	ce::graphics::Text text;
	text.setFont(&font);
	text.setColor(1.0f, 0.0f, 0.0f);
	text.setSize(30);

	ce::graphics::ShaderLoader sLoader;
	ce::graphics::ShaderProperties props;
	props.vPath = "Shaders/Text/basic_vertex.glsl";
	props.fPath = "Shaders/Text/basic_fragment.glsl";
	ce::graphics::Shader textShader = sLoader.loadShader(props);

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
					// Buggy on linux it seems - probably happens too fast, so it instantly switches back
					if (fullscreen == false)
					{
						window.setWindowFullscreen(ce::core::WINDOW_FULLSCREEN_DESKTOP);
						ce::core::Application::setScreenBufferSize(window.getSize().x, window.getSize().y);
						fullscreen = true;
					}
					else
					{
						window.setWindowFullscreen(0);
						ce::core::Application::setScreenBufferSize(window.getSize().x, window.getSize().y);
						fullscreen = false;
					}
				}

				if (e.key.keysym.sym == SDLK_F9)
				{
					showFPS = !showFPS; // Toggle fps counter
				}
			}
		}

		window.clear();
		glClear(GL_DEPTH_BUFFER_BIT);

		float deltaTime = clock.restart().asSeconds();

		exGameMode.begin();
		exGameMode.tick(deltaTime);
		exGameMode.draw();
		exGameMode.end();
		
		if (showFPS)
		{
			// Draw fps - Temporary, will create debug panel thingy
			frameCount += deltaTime;
			if (frameCount >= 1.f) // Once a second
			{
				int fps = 1 / deltaTime;
				text.setPosition(20, window.getSize().y - 30);
				text.setText("FPS: " + std::to_string(fps));

				frameCount = 0.f;
			}
			text.draw(textShader);
		}
		
		window.display();
	}

	SDL_Quit();

	return 0;
}

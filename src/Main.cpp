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
	lu::core::Application::init();
	lu::core::Application::setScreenBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	lu::core::Application::getInstance().maxDirLights = 1;
	lu::core::Application::getInstance().maxPointLights = 10;
	lu::core::Application::getInstance().maxSpotLights = 1;

	lu::core::Window window(
		"Lucent",
		lu::core::WINDOWPOS_CENTERED,
		lu::core::WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		lu::core::WINDOW_RESIZABLE
	);

	lu::core::Application::enableVSYNC(true);

	window.setWindowGrab(true);

	lu::game::ExampleGameMode exGameMode;
	exGameMode.init();

	glEnable(GL_DEPTH_TEST);

	lu::core::Clock clock;
	clock.start();

	// FPS -- TEMP, gonna do better
	bool showFPS = false;
	float frameCount = 1.0f;
	lu::graphics::Font font;
	font.load("Resources/Fonts/MotionControl-Bold.otf");
	lu::graphics::Text text;
	text.setFont(&font);
	text.setColor(1.0f, 1.0f, 1.0f);
	text.setSize(30);

	lu::graphics::ShaderLoader sLoader;
	lu::graphics::ShaderProperties props;
	props.vPath = "Shaders/Text/basic_vertex.glsl";
	props.fPath = "Shaders/Text/basic_fragment.glsl";
	lu::graphics::Shader textShader = sLoader.loadShader(props, false);

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
						window.setWindowFullscreen(lu::core::WINDOW_FULLSCREEN_DESKTOP);
						lu::core::Application::setScreenBufferSize(window.getSize().x, window.getSize().y);
						fullscreen = true;
					}
					else
					{
						window.setWindowFullscreen(0);
						lu::core::Application::setScreenBufferSize(window.getSize().x, window.getSize().y);
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

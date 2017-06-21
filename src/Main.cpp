#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Core/Input.h"
#include "Core/Window.h"
#include "Core/Application.h"

#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/Model.h"
#include "Graphics/Lights.h"

#include "Graphics/Scene.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float cameraYaw = 0.0f;
bool fullscreen = false;

// Also in CMakeLists.txt
// TODO: on WIN32 copy dlls into build directories Debug and Release
// TODO: Create build scripts ? Windows and linux(ubuntu) makes testing the engine faster even if just a few minutes faster
// TODO TODO TODO TODO
// TODO TODO TODO TODO
// TODO TODO TODO TODO
// TODO TODO TODO TODO

int main(int argc, char* argv[])
{
	ce::core::Application::getInstance().init();
	ce::core::Application::getInstance().screenWidth = SCREEN_WIDTH;
	ce::core::Application::getInstance().screenHeight = SCREEN_HEIGHT;

	ce::core::Window window(
		"Hello world",
		ce::core::WINDOWPOS_CENTERED,
		ce::core::WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		ce::core::WINDOW_RESIZABLE
	);

	window.setWindowGrab(true);

	ce::graphics::Model model("Resources/Models/Nanosuit/nanosuit.obj");
	model.translate(glm::vec3(-1.0f, -1.0f, -1.0f));
	model.scale(glm::vec3(0.1f, 0.1f, 0.1f));

	ce::graphics::Model model1("Resources/Models/Nanosuit/nanosuit.obj");
	model1.rotate(45.f, glm::vec3(0.0f, 1.0f, 0.0f));
	model1.translate(glm::vec3(1.0f, -1.0f, 1.0f));
	model1.scale(glm::vec3(0.1f, 0.1f, 0.1f));

	ce::graphics::Model model2("Resources/Models/Nanosuit/nanosuit.obj");
	model2.rotate(120.f, glm::vec3(0.0f, 1.0f, 0.0f));
	model2.translate(glm::vec3(-1.0f, -1.0f, -1.0f));
	model2.scale(glm::vec3(0.1f, 0.1f, 0.1f));

	ce::graphics::Scene scene;
	scene.addModel(model);
	scene.addModel(model1);
	scene.addModel(model2);

	ce::graphics::DirLight dirLight;
	dirLight.direction = glm::vec3(0.0f, -0.5f, 0.5f);
	dirLight.ambient = glm::vec3(0.8f, 0.2f, 0.2f);
	scene.addDirLight(dirLight);
	
	ce::graphics::PointLight pointLight;
	scene.addPointLight(pointLight);

	ce::graphics::SpotLight spotLight;
	scene.addSpotLight(spotLight);

	ce::graphics::Camera camera;

	glEnable(GL_DEPTH_TEST);

	bool running = true;
	while (running)
	{
		Uint32 ticks = SDL_GetTicks();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}

			// TODO TEMP TEMP vvvv
			if (e.type == SDL_MOUSEMOTION)
			{
				cameraYaw	+= e.motion.xrel;
				cameraYaw = glm::mod(cameraYaw, 360.f);
				camera.resetOriantation();
				camera.yaw(cameraYaw);
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

				else if (e.key.keysym.sym == SDLK_w)
					camera.translate(0.f, 0.f, 0.1f);
				else if (e.key.keysym.sym == SDLK_s)
					camera.translate(0.f, 0.f, -0.1f);
				if (e.key.keysym.sym == SDLK_a)
					camera.translate(0.1f, 0.f, 0.f);
				else if (e.key.keysym.sym == SDLK_d)
					camera.translate(-0.1f, 0.f, 0.f);

				else if (e.key.keysym.sym == SDLK_1)
					camera.setFOV(45.f);
				else if (e.key.keysym.sym == SDLK_2)
					camera.setFOV(80.f);

			}
			// TODO TEMP TEMP ^^^^
		}

		window.clear();
		
		glClear(GL_DEPTH_BUFFER_BIT); // Depth buffer

		scene.draw(camera);

		window.display();
	}

	SDL_Quit();

	return 0;
}
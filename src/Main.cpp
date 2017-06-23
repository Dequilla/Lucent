#include <iostream>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "Core/Time.h"
#include "Core/Input.h"
#include "Core/Window.h"
#include "Core/Application.h"

#include "Graphics/Shader/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/Lights.h"

#include "Graphics/Model/ModelLoader.h"
#include "Graphics/Model/Model.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

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

	ce::graphics::Camera camera;

	ce::core::Clock clock;

	ce::graphics::ModelLoader loader;
	ce::graphics::Model		  model;
	ce::graphics::Model		  model1;

	clock.start();
	model1 = loader.loadModel("Resources/Models/Nanosuit/nanosuit.obj");
	model = loader.loadModel("Resources/Models/TestWindow/test-window.obj");
	std::cout << "Loading models took: " << clock.getPassed().asSeconds() << "s" << std::endl;

	// When loading shaders there is only ever one instance created even if you load it elsewhere with the same paths specified
	ce::graphics::Shader shaderOpaque("Shaders/opaque_sd_vertex.glsl", "Shaders/opaque_sd_fragment.glsl");
	ce::graphics::Shader shaderTransparent("Shaders/transparent_sd_vertex.glsl", "Shaders/transparent_sd_fragment.glsl");
	
	glEnable(GL_DEPTH_TEST);

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
		
		glClear(GL_DEPTH_BUFFER_BIT);

		// LIGHTS OPAQUE SHADER
		// Dir
		{
		ce::graphics::DirLight dLight;
		ce::graphics::PointLight pLight;
		ce::graphics::SpotLight sLight;

		shaderOpaque.use();
		shaderOpaque.setVec3("dirLights[0].ambient", dLight.ambient);
		shaderOpaque.setVec3("dirLights[0].diffuse", dLight.diffuse);
		shaderOpaque.setVec3("dirLights[0].specular", dLight.specular);
		shaderOpaque.setVec3("dirLights[0].direction", dLight.direction);

		// Point
		shaderOpaque.setVec3("pointLights[0].ambient", pLight.ambient);
		shaderOpaque.setVec3("pointLights[0].diffuse", pLight.diffuse);
		shaderOpaque.setVec3("pointLights[0].specular", pLight.specular);
		shaderOpaque.setVec3("pointLights[0].position", pLight.position);

		shaderOpaque.setFloat("pointLights[0].constant", pLight.constant);
		shaderOpaque.setFloat("pointLights[0].linear", pLight.linear);
		shaderOpaque.setFloat("pointLights[0].quadratic", pLight.quadratic);

		// Spot
		shaderOpaque.setVec3("spotLights[0].ambient", sLight.ambient);
		shaderOpaque.setVec3("spotLights[0].diffuse", sLight.diffuse);
		shaderOpaque.setVec3("spotLights[0].specular", sLight.specular);

		shaderOpaque.setVec3("spotLights[0].position", sLight.position);
		shaderOpaque.setVec3("spotLights[0].direction", sLight.direction);

		shaderOpaque.setFloat("spotLights[0].constant", sLight.constant);
		shaderOpaque.setFloat("spotLights[0].linear", sLight.linear);
		shaderOpaque.setFloat("spotLights[0].quadratic", sLight.quadratic);

		shaderOpaque.setFloat("spotLights[0].cutOff", sLight.cutOff);
		shaderOpaque.setFloat("spotLights[0].outerCutOff", sLight.outerCutOff);

		// LIGHTS TRANSPARENT SHADER
		// Dir
		shaderTransparent.use();
		shaderTransparent.setVec3("dirLights[0].ambient", dLight.ambient);
		shaderTransparent.setVec3("dirLights[0].diffuse", dLight.diffuse);
		shaderTransparent.setVec3("dirLights[0].specular", dLight.specular);
		shaderTransparent.setVec3("dirLights[0].direction", dLight.direction);

		// Point
		shaderTransparent.setVec3("pointLights[0].ambient", pLight.ambient);
		shaderTransparent.setVec3("pointLights[0].diffuse", pLight.diffuse);
		shaderTransparent.setVec3("pointLights[0].specular", pLight.specular);
		shaderTransparent.setVec3("pointLights[0].position", pLight.position);

		shaderTransparent.setFloat("pointLights[0].constant", pLight.constant);
		shaderTransparent.setFloat("pointLights[0].linear", pLight.linear);
		shaderTransparent.setFloat("pointLights[0].quadratic", pLight.quadratic);

		// Spot
		shaderTransparent.setVec3("spotLights[0].ambient", sLight.ambient);
		shaderTransparent.setVec3("spotLights[0].diffuse", sLight.diffuse);
		shaderTransparent.setVec3("spotLights[0].specular", sLight.specular);

		shaderTransparent.setVec3("spotLights[0].position", sLight.position);
		shaderTransparent.setVec3("spotLights[0].direction", sLight.direction);

		shaderTransparent.setFloat("spotLights[0].constant", sLight.constant);
		shaderTransparent.setFloat("spotLights[0].linear", sLight.linear);
		shaderTransparent.setFloat("spotLights[0].quadratic", sLight.quadratic);

		shaderTransparent.setFloat("spotLights[0].cutOff", sLight.cutOff);
		shaderTransparent.setFloat("spotLights[0].outerCutOff", sLight.outerCutOff);
		}
		// Camera
		shaderOpaque.use();
		shaderOpaque.setMat4("view", camera.getViewMatrix());
		shaderOpaque.setMat4("projection", camera.getProjectionMatrix());

		shaderTransparent.use();
		shaderTransparent.setMat4("view", camera.getViewMatrix());
		shaderTransparent.setMat4("projection", camera.getProjectionMatrix());
		
		// Suit
		glDisable(GL_BLEND);
		glm::mat4 modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.3f, -3.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
		shaderOpaque.use();
		shaderOpaque.setMat4("model", modelMatrix);
		shaderTransparent.use();
		shaderTransparent.setMat4("model", modelMatrix);
		model1.draw();

		// Window
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		modelMatrix = glm::mat4();
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.3f, -3.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians((float)clock.getPassed().asMilliseconds() / 20.f), glm::vec3(0.0f, 1.0f, 0.0f));
		shaderOpaque.use();
		shaderOpaque.setMat4("model", modelMatrix);
		shaderTransparent.use();
		shaderTransparent.setMat4("model", modelMatrix);
		model.draw();
		
		window.display();
	}

	SDL_Quit();

	return 0;
}
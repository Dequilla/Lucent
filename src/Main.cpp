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

#include "Graphics/Model.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

float cameraYaw = 0.0f;
float cameraPitch = 0.0f;
bool fullscreen = false;

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

	ce::graphics::Shader testShader("Shaders/vertex_test.glsl", "Shaders/fragment_test.glsl");
	ce::graphics::Camera camera;

	ce::graphics::Model model("Resources/Models/Nanosuit/nanosuit.obj");

	// TODO TODO TODO
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
		
		testShader.use();
		glClear(GL_DEPTH_BUFFER_BIT); // Depth buffer

		glm::mat4 view;
		glm::mat4 projection;
		view = camera.getViewMatrix();
		projection = camera.getProjectionMatrix();

		testShader.setMat4("projection", projection);
		testShader.setMat4("view", view);

		glm::mat4 modelMatrix;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -1.0f, -3.0f));
		modelMatrix = glm::rotate(modelMatrix, glm::radians((float)ticks / 50), glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.09f, 0.09f, 0.09f));
		testShader.setMat4("model", modelMatrix);

		testShader.setFloat("material.shininess", 64.0f);
		testShader.setVec3("viewPos", camera.getPosition()); // Camera Position (not matrix)

		// Directional light
		testShader.setVec3("dirLights[0].direction", -0.2f, 0.0f, -0.3f);
		testShader.setVec3("dirLights[0].ambient", 0.05f, 0.05f, 0.05f);
		testShader.setVec3("dirLights[0].diffuse", 0.4f, 0.4f, 0.4f);
		testShader.setVec3("dirLights[0].specular", 0.5f, 0.5f, 0.5f);

		// Point light
		testShader.setVec3("pointLights[0].position", 3.0, 0.0, 1.0);
		testShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		testShader.setVec3("pointLights[0].diffuse", 0.8f, 0.1f, 0.1f);
		testShader.setVec3("pointLights[0].specular", 1.0f, 0.0f, 0.0f);
		testShader.setFloat("pointLights[0].constant", 1.0f);
		testShader.setFloat("pointLights[0].linear", 0.09);
		testShader.setFloat("pointLights[0].quadratic", 0.032);

		// Spot light
		testShader.setVec3("spotLights[0].position", -camera.getPosition().x, camera.getPosition().y, -camera.getPosition().z);
		testShader.setVec3("spotLights[0].direction", camera.getForwardVector());
		testShader.setVec3("spotLights[0].ambient", 0.0f, 0.0f, 0.0f);
		testShader.setVec3("spotLights[0].diffuse", 1.0f, 1.0f, 1.0f);
		testShader.setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
		testShader.setFloat("spotLights[0].constant", 1.0f);
		testShader.setFloat("spotLights[0].linear", 0.09);
		testShader.setFloat("spotLights[0].quadratic", 0.032);
		testShader.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(15.f)));
		testShader.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(25.0f)));

		model.draw(testShader);

		window.display();
	}

	SDL_Quit();

	return 0;
}
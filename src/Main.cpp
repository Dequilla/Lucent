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
#include "Graphics/Shader/ShaderLoader.h"

#include "Graphics/Renderer/ForwardRenderer.h"

#include "Graphics/Camera.h"
#include "Graphics/Texture.h"
#include "Graphics/Lights.h"


#include "Graphics/Model/ModelLoader.h"
#include "Graphics/Model/Model.h"

#include "Game/GameObject.h"
#include "Game/Scene.h"
#include "Game/Components/ComponentIncludes.h"

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

#include "Core/Utility/log.h"

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
	ce::graphics::Model		  modelGrass;

	clock.start();
	model = loader.loadModel("Resources/Models/TestWindow/test-window.obj");
	modelGrass = loader.loadModel("Resources/Models/TestGrass/untitled.obj");
	ce::core::log("Loading models took: " + std::to_string(clock.getPassed().asSeconds()));

	ce::graphics::ForwardRenderer renderer;
	renderer.init();
	renderer.setScreenBufferSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	ce::graphics::ShaderProperties properties;
	ce::graphics::ShaderLoader sLoader;

	// Opaque
	properties.vPath = "Shaders/Dynamic/opaque_sd_vertex.glsl";
	properties.fPath = "Shaders/Dynamic/opaque_sd_fragment.glsl";
	properties.numDirLights = 1;
	properties.numPointLights = 1;
	properties.numSpotLights = 1;
	ce::graphics::Shader* shaderOpaque = sLoader.loadShader(properties);

	// Transparent
	properties.vPath = "Shaders/Dynamic/transparent_sd_vertex.glsl";
	properties.fPath = "Shaders/Dynamic/transparent_sd_fragment.glsl";
	ce::graphics::Shader* shaderTransparent = sLoader.loadShader(properties);

	glEnable(GL_DEPTH_TEST);

	// Scene
	ce::game::Scene scene;
	ce::game::ModelComponent modelComp;
	ce::game::TransformComponent transComp;
	modelComp.setModel(model);
	ce::game::GameObject modelObj;
	modelObj.name = "model1";
	modelObj.setParent(scene.getRootObject());
	modelObj.addComponent(&modelComp);
	modelObj.addComponent(&transComp);
	scene.getRootObject()->addChild(modelObj);

	scene.init();

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

				else if (e.key.keysym.sym == SDLK_UP)
					transComp.move(glm::vec3(0.0f, 0.0f, -0.1f));
				else if (e.key.keysym.sym == SDLK_DOWN)
					transComp.move(glm::vec3(0.0f, 0.0f, 0.1f));
				else if (e.key.keysym.sym == SDLK_LEFT)
					transComp.yaw(10.f);
				else if (e.key.keysym.sym == SDLK_RIGHT)
					transComp.yaw(-10.f);
			}
			// TODO TEMP TEMP ^^^^
		}

		window.clear();
		glClear(GL_DEPTH_BUFFER_BIT);

		ce::graphics::DirLight dLight;
		ce::graphics::PointLight pLight;
		ce::graphics::SpotLight sLight;
		
		ce::graphics::LightSetup lights;
		lights.dirLights.push_back(dLight);
		lights.pointLights.push_back(pLight);
		lights.spotLights.push_back(sLight);

		scene.begin();
		renderer.begin();
		renderer.beginScene(&camera);
		renderer.submitLightSetup(lights);

		scene.tick(1.f);
		scene.draw(&renderer);

		renderer.endScene();
		scene.end();
		renderer.end();
		
		renderer.present();

		window.display();
	}

	SDL_Quit();

	return 0;
}

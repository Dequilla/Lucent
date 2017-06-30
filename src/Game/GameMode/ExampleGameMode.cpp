#include "ExampleGameMode.h"

void ce::game::ExampleGameMode::begin()
{
	m_renderer.begin();
	m_renderer.beginScene(&m_camera);

	GameMode::begin();
}

void ce::game::ExampleGameMode::init()
{
	// Game objects
	ce::game::GameObject model;
	ce::graphics::ModelLoader loader;
	ce::graphics::Model nanosuit = loader.loadModel("Resources/Models/Nanosuit/nanosuit.obj");

	m_modelComponent.setModel(nanosuit);
	m_transformComponent.setScale(0.2f, 0.2f, 0.2f);
	m_transformComponent.move(0.0f, -0.1f, 0.0f);

	model.name = "nanosuit";
	model.setParent(m_scene.getRootObject());
	model.addComponent(&m_modelComponent);
	model.addComponent(&m_transformComponent);
	m_scene.getRootObject()->addChild(model);

	ce::game::GameObject grassy;
	ce::graphics::Model grassyModel = loader.loadModel("Resources/Models/Grassy/grassy.obj");

	m_modelComponentGrassy.setModel(grassyModel);
	m_transformComponentGrassy.setPosition(0.0f, -1.f, 0.0f);
	m_transformComponentGrassy.setScale(2.f, 2.f, 2.f);

	grassy.name = "grassy";
	grassy.setParent(m_scene.getRootObject());
	grassy.addComponent(&m_modelComponentGrassy);
	grassy.addComponent(&m_transformComponentGrassy);
	m_scene.getRootObject()->addChild(grassy);

	// Lights
	ce::graphics::DirLight dLight;
	dLight.ambient = glm::vec3(0.005f, 0.005f, 0.005f);
	dLight.diffuse = glm::vec3(0.02f, 0.02f, 0.02f);
	dLight.specular = glm::vec3(0.03f, 0.03f, 0.03f);
	ce::graphics::PointLight pLight;
	pLight.position = glm::vec3(0.0f, 3.0f, 1.0f);
	pLight.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	pLight.constant = 0.1f;
	ce::graphics::SpotLight sLight;

	m_lights.dirLights.push_back(dLight);
	m_lights.pointLights.push_back(pLight);
	m_lights.spotLights.push_back(sLight);

	// Input
	m_input.bindAxisEvent(ce::core::M_MOTION_XREL, this, &ExampleGameMode::cameraYaw);
	m_input.bindAxisEvent(ce::core::M_MOTION_YREL, this, &ExampleGameMode::cameraPitch);

	m_input.bindButtonEvent(ce::core::K_w, this, &ExampleGameMode::moveForward);
	m_input.bindButtonEvent(ce::core::K_s, this, &ExampleGameMode::moveBackward);
	m_input.bindButtonEvent(ce::core::K_a, this, &ExampleGameMode::moveLeft);
	m_input.bindButtonEvent(ce::core::K_d, this, &ExampleGameMode::moveRight);

	m_input.bindButtonEvent(ce::core::K_KP_8, this, &ExampleGameMode::movePLightF);
	m_input.bindButtonEvent(ce::core::K_KP_2, this, &ExampleGameMode::movePLightB);
	m_input.bindButtonEvent(ce::core::K_KP_4, this, &ExampleGameMode::movePLightL);
	m_input.bindButtonEvent(ce::core::K_KP_6, this, &ExampleGameMode::movePLightR);

	GameMode::init();
}

void ce::game::ExampleGameMode::tick(float dt)
{
	float speed = 20.0f * dt;

	if (m_moveForward)
	{
		m_camera.translate(0.f, 0.f, speed);
	}

	if (m_moveBackward)
	{
		m_camera.translate(0.f, 0.f, -speed);
	}

	if (m_moveLeft)
	{
		m_camera.translate(speed, 0.f, 0.f);
	}

	if (m_moveRight)
	{
		m_camera.translate(-speed, 0.f, 0.f);
	}

	m_camera.setRotationEularXYZ(m_orientPitch, m_orientYaw, 0.0f);

	GameMode::tick(dt);
}

void ce::game::ExampleGameMode::draw()
{
	m_renderer.submitLightSetup(m_lights);

	GameMode::draw(&m_renderer);
}

void ce::game::ExampleGameMode::end()
{
	m_renderer.endScene();
	m_renderer.end();

	m_renderer.present();

	GameMode::end();
}

void ce::game::ExampleGameMode::cameraYaw(float axis)
{
	m_orientYaw += axis * 0.5f;
}

void ce::game::ExampleGameMode::cameraPitch(float axis)
{
	m_orientPitch += axis * 0.5f;
	
	if (m_orientPitch > 89.9f)
		m_orientPitch = 89.9f;
	else if (m_orientPitch < -89.9f)
		m_orientPitch = -89.9f;
}

void ce::game::ExampleGameMode::moveLeft(bool pressed)
{
	m_moveLeft = pressed;
}

void ce::game::ExampleGameMode::moveRight(bool pressed)
{
	m_moveRight = pressed;
}

void ce::game::ExampleGameMode::moveForward(bool pressed)
{
	m_moveForward = pressed;
}

void ce::game::ExampleGameMode::moveBackward(bool pressed)
{
	m_moveBackward = pressed;
}

void ce::game::ExampleGameMode::movePLightF(bool pressed)
{
	m_lights.pointLights.at(0).position += glm::vec3(0.0f, 0.0f, -0.2f);
}

void ce::game::ExampleGameMode::movePLightB(bool pressed)
{
	m_lights.pointLights.at(0).position += glm::vec3(0.0f, 0.0f, 0.2f);
}

void ce::game::ExampleGameMode::movePLightL(bool pressed)
{
	m_lights.pointLights.at(0).position += glm::vec3(-0.2f, 0.0f, 0.0f);
}

void ce::game::ExampleGameMode::movePLightR(bool pressed)
{
	m_lights.pointLights.at(0).position += glm::vec3(0.2f, 0.0f, 0.0f);
}
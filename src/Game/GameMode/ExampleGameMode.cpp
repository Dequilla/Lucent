#include "Game/GameMode/ExampleGameMode.h"

void lu::game::ExampleGameMode::init()
{
	glm::vec2 size = lu::core::Application::getScreenBufferSize();

	m_renderer.setScreenBufferSize(size.x, size.y);

	

	// Game objects
	lu::graphics::ModelLoader loader;
	
	lu::graphics::Model grassyModel = loader.loadModel("Resources/Models/TestTerrain/TestTerrain.obj");

	m_grassy.name = "grassy";
	m_grassy.model()->setModel(grassyModel);
	m_grassy.transform()->setPosition(0.0f, -15.f, 0.0f);
	m_grassy.transform()->setScale(1.f, 1.f, 1.f);
	m_scene.addGameObject("root", &m_grassy);

	lu::graphics::Model nanosuit = loader.loadModel("Resources/Models/Nanosuit/nanosuit.obj");

	m_nanosuit.name = "nanosuit";
	m_nanosuit.model()->setModel(nanosuit);
	m_nanosuit.transform()->setScale(0.2f, 0.2f, 0.2f);
	m_nanosuit.transform()->move(0.0f, 0.2f, 0.0f);
	m_scene.addGameObject("root", &m_nanosuit);

	// Camera - a gameobject(extended to CameraObject)
	m_camera.name = "camera";
	m_camera.camera()->setProjection(80.f, (float)size.x / (float)size.y, 0.1f, 100.0f);
	m_camera.transform()->setPosition(0.0f, -2.0f, -3.0f);
	m_scene.addGameObject("root", &m_camera);

	// Lights
	m_dirLight.light()->ambient = glm::vec3(0.01f, 0.01f, 0.01f);
	m_dirLight.light()->diffuse = glm::vec3(0.02f, 0.02f, 0.02f);
	m_dirLight.light()->specular = glm::vec3(0.03f, 0.03f, 0.03f);
	m_scene.addGameObject("root", &m_dirLight);

	m_pointLights[0].light()->position = glm::vec3(0.0f, 2.f, 0.0f);
	m_pointLights[0].light()->diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	m_pointLights[0].light()->constant = 0.5f;
	m_pointLights[0].light()->linear = 0.022f;
	m_pointLights[0].light()->quadratic = 0.0019f;
	m_scene.addGameObject("root", &m_pointLights[0]);

	m_pointLights[1].light()->position = glm::vec3(10.0f, 2.f, 10.0f);
	m_pointLights[1].light()->diffuse = glm::vec3(0.7f, 0.7f, 0.2f);
	m_pointLights[1].light()->constant = 0.5f;
	m_pointLights[1].light()->linear = 0.022f;
	m_pointLights[1].light()->quadratic = 0.0019f;
	m_scene.addGameObject("root", &m_pointLights[1]);

	m_spotLight.light()->ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	m_spotLight.light()->diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	m_spotLight.light()->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	m_scene.addGameObject("root", &m_spotLight);

	// Input
	m_input.bindAxisEvent(lu::core::M_MOTION_XREL, this, &ExampleGameMode::cameraYaw);
	m_input.bindAxisEvent(lu::core::M_MOTION_YREL, this, &ExampleGameMode::cameraPitch);

	m_input.bindButtonEvent(lu::core::K_w, this, &ExampleGameMode::moveForward);
	m_input.bindButtonEvent(lu::core::K_s, this, &ExampleGameMode::moveBackward);
	m_input.bindButtonEvent(lu::core::K_a, this, &ExampleGameMode::moveLeft);
	m_input.bindButtonEvent(lu::core::K_d, this, &ExampleGameMode::moveRight);

	m_input.bindButtonEvent(lu::core::K_h, this, &ExampleGameMode::movePLightF);
	m_input.bindButtonEvent(lu::core::K_j, this, &ExampleGameMode::movePLightB);
	m_input.bindButtonEvent(lu::core::K_k, this, &ExampleGameMode::movePLightL);
	m_input.bindButtonEvent(lu::core::K_l, this, &ExampleGameMode::movePLightR);

	GameMode::init();
}

void lu::game::ExampleGameMode::begin()
{
	glm::vec2 size = lu::core::Application::getScreenBufferSize();
	m_renderer.setScreenBufferSize(size.x, size.y);

	m_renderer.begin();
	m_renderer.beginScene(m_camera.camera()->getViewMatrix(), m_camera.camera()->getProjectionMatrix());

	GameMode::begin();
}

void lu::game::ExampleGameMode::tick(float dt)
{
	float speed = 10.0f * dt;

	if (m_moveForward)
	{
		m_camera.transform()->translate(0.f, 0.f, speed);
	}

	if (m_moveBackward)
	{
		m_camera.transform()->translate(0.f, 0.f, -speed);
	}

	if (m_moveLeft)
	{
		m_camera.transform()->translate(speed, 0.f, 0.f);
	}

	if (m_moveRight)
	{
		m_camera.transform()->translate(-speed, 0.f, 0.f);
	}

	m_camera.transform()->setRotation(m_orientPitch, m_orientYaw, 0.0f);
	
	m_spotLight.light()->position = glm::vec3(-m_camera.transform()->getPosition().x, -m_camera.transform()->getPosition().y, -m_camera.transform()->getPosition().z);
	m_spotLight.light()->direction = m_camera.camera()->getForwardVector();

	GameMode::tick(dt);
}

void lu::game::ExampleGameMode::draw()
{
	GameMode::draw(&m_renderer);
}

void lu::game::ExampleGameMode::end()
{
	m_renderer.endScene();
	m_renderer.end();

	m_renderer.present(); // The "actual" drawing of everything to screen

	GameMode::end();
}

void lu::game::ExampleGameMode::cameraYaw(float axis)
{
	m_orientYaw += axis * 0.5f;
}

void lu::game::ExampleGameMode::cameraPitch(float axis)
{
	m_orientPitch += axis * 0.5f;
	
	if (m_orientPitch > 89.9f)
		m_orientPitch = 89.9f;
	else if (m_orientPitch < -89.9f)
		m_orientPitch = -89.9f;
}

void lu::game::ExampleGameMode::moveLeft(bool pressed)
{
	m_moveLeft = pressed;
}

void lu::game::ExampleGameMode::moveRight(bool pressed)
{
	m_moveRight = pressed;
}

void lu::game::ExampleGameMode::moveForward(bool pressed)
{
	m_moveForward = pressed;
}

void lu::game::ExampleGameMode::moveBackward(bool pressed)
{
	m_moveBackward = pressed;
}

void lu::game::ExampleGameMode::movePLightF(bool pressed)
{
	m_pointLights[0].light()->position += glm::vec3(0.0f, 0.0f, -0.2f);
	m_nanosuit.transform()->move(glm::vec3(0.0f, 0.0f, -0.2f));
}

void lu::game::ExampleGameMode::movePLightB(bool pressed)
{
	m_pointLights[0].light()->position += glm::vec3(0.0f, 0.0f, 0.2f);
	m_nanosuit.transform()->move(glm::vec3(0.0f, 0.0f, 0.2f));
}

void lu::game::ExampleGameMode::movePLightL(bool pressed)
{
	m_pointLights[0].light()->position += glm::vec3(-0.2f, 0.0f, 0.0f);
	m_nanosuit.transform()->move(glm::vec3(-0.2f, 0.0f, 0.0f));
}

void lu::game::ExampleGameMode::movePLightR(bool pressed)
{
	m_pointLights[0].light()->position += glm::vec3(0.2f, 0.0f, 0.0f);
	m_nanosuit.transform()->move(glm::vec3(0.2f, 0.0f, 0.0f));
}
#include "GameMode.h"

void ce::game::GameMode::checkInput(const SDL_Event& input)
{
	m_input.checkInput(input);
}

void ce::game::GameMode::begin()
{
	m_scene.begin();
}

void ce::game::GameMode::init()
{
	m_scene.init();
}

void ce::game::GameMode::tick(float dt)
{
	m_scene.tick(dt);
}

void ce::game::GameMode::end()
{
	m_scene.end();
}

void ce::game::GameMode::draw(ce::graphics::Renderer3D* renderer)
{
	m_scene.draw(renderer);
}
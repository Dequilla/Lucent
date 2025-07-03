#include "Game/GameMode/GameMode.h"

void
lu::game::GameMode::checkInput(const SDL_Event &input)
{
    m_input.checkInput(input);
}

void
lu::game::GameMode::init()
{
    m_scene.init();
}

void
lu::game::GameMode::begin()
{
    m_scene.begin();
}

void
lu::game::GameMode::tick(float dt)
{
    m_scene.tick(dt);
}

void
lu::game::GameMode::end()
{
    m_scene.end();
}

void
lu::game::GameMode::draw(lu::graphics::Renderer3D *renderer)
{
    m_scene.draw(renderer);
}
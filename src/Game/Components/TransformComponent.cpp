#include "Game/Components/TransformComponent.h"

void
lu::game::TransformComponent::init()
{
    bTickable = false;
    bDrawable = false;
}

void
lu::game::TransformComponent::tick(float dt)
{
}

void
lu::game::TransformComponent::draw(lu::graphics::Renderer3D *renderer)
{
}

std::string
lu::game::TransformComponent::getType()
{
    return std::string("TransformComponent");
}
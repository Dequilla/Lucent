#include "TransformComponent.h"

void ce::game::TransformComponent::init()
{
	bTickable = false;
	bDrawable = false;
}

void ce::game::TransformComponent::tick(float dt)
{
}

void ce::game::TransformComponent::draw(ce::graphics::Renderer3D * renderer)
{
}

std::string ce::game::TransformComponent::getType()
{
	return std::string("TransformComponent");
}
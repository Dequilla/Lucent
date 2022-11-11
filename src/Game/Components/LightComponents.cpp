#include "Game/Components/LightComponents.h"

void lu::game::DirLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void lu::game::DirLightComponent::tick(float dt)
{
}

void lu::game::DirLightComponent::draw(lu::graphics::Renderer3D * renderer)
{
	renderer->submitDirLight(*this);
}

void lu::game::PointLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void lu::game::PointLightComponent::tick(float dt)
{
}

void lu::game::PointLightComponent::draw(lu::graphics::Renderer3D * renderer)
{
	renderer->submitPointLight(*this);
}

void lu::game::SpotLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void lu::game::SpotLightComponent::tick(float dt)
{
}

void lu::game::SpotLightComponent::draw(lu::graphics::Renderer3D * renderer)
{
	renderer->submitSpotLight(*this);
}
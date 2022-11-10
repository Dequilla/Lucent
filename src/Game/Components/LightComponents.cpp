#include "Game/Components/LightComponents.h"

void ce::game::DirLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void ce::game::DirLightComponent::tick(float dt)
{
}

void ce::game::DirLightComponent::draw(ce::graphics::Renderer3D * renderer)
{
	renderer->submitDirLight(*this);
}

void ce::game::PointLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void ce::game::PointLightComponent::tick(float dt)
{
}

void ce::game::PointLightComponent::draw(ce::graphics::Renderer3D * renderer)
{
	renderer->submitPointLight(*this);
}

void ce::game::SpotLightComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void ce::game::SpotLightComponent::tick(float dt)
{
}

void ce::game::SpotLightComponent::draw(ce::graphics::Renderer3D * renderer)
{
	renderer->submitSpotLight(*this);
}
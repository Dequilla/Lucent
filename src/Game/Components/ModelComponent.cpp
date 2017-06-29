#include "ModelComponent.h"

void ce::game::ModelComponent::init()
{
	bTickable = false;
	bDrawable = true;
}

void ce::game::ModelComponent::tick(float dt)
{
}

void ce::game::ModelComponent::draw(ce::graphics::Renderer3D* renderer)
{
	// We only care about the first one, having multiple transforms wouldnt make much sense
	TransformComponent* transform = getHostComponentsOfType<TransformComponent>("TransformComponent").at(0);
	glm::mat4 modelMatrix = transform->getAsModelMatrix();
	m_model.draw(renderer, modelMatrix);
}

std::string ce::game::ModelComponent::getType()
{
	return std::string("ModelComponent");
}

void ce::game::ModelComponent::setModel(ce::graphics::Model model)
{
	m_model = model;
}
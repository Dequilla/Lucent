#include "ModelComponent.h"

void ce::game::ModelComponent::init()
{
	bTickable = false;
	bDrawable = true;

	updateTransform();
}

void ce::game::ModelComponent::tick(float dt)
{
}

void ce::game::ModelComponent::draw(ce::graphics::Renderer3D* renderer)
{
	glm::mat4 modelMatrix;

	// If we do not have a transform get a default matrix
	if (m_transform == nullptr)
	{
		modelMatrix = glm::mat4();
		updateTransform(); // And try to update it
	}
	else
		modelMatrix = m_transform->getAsMatrix();

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

void ce::game::ModelComponent::updateTransform()
{
	// Get the first TransformComponent of our host
	m_transform = getHostComponentsOfType<TransformComponent>("TransformComponent").at(0);
}
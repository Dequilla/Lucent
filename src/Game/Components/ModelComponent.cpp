#include "Game/Components/ModelComponent.h"

void
lu::game::ModelComponent::init()
{
    bTickable = false;
    bDrawable = true;

    updateTransform();
}

void
lu::game::ModelComponent::tick(float dt)
{
}

void
lu::game::ModelComponent::draw(lu::graphics::Renderer3D *renderer)
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

std::string
lu::game::ModelComponent::getType()
{
    return std::string("ModelComponent");
}

void
lu::game::ModelComponent::setModel(lu::graphics::Model model)
{
    m_model = model;
}

void
lu::game::ModelComponent::updateTransform()
{
    // Get the first TransformComponent of our host
    m_transform =
      getHostComponentsOfType<TransformComponent>("TransformComponent").at(0);
}
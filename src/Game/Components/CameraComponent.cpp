#include "Game/Components/CameraComponent.h"

lu::game::CameraComponent::CameraComponent()
{
    glm::vec2 size = lu::core::Application::getScreenBufferSize();

    m_aspectRatio = (float)size.x / (float)size.y;
}

void
lu::game::CameraComponent::init()
{
    bDrawable = false;
    bTickable = false;

    updateTransform();
}

void
lu::game::CameraComponent::tick(float dt)
{
}

void
lu::game::CameraComponent::draw(lu::graphics::Renderer3D *renderer)
{
}

std::string
lu::game::CameraComponent::getType()
{
    return std::string("CameraComponent");
}

void
lu::game::CameraComponent::setProjection(float fov,
                                         float aspectRatio,
                                         float projnear,
                                         float projfar)
{
    m_fov = fov;
    m_aspectRatio = aspectRatio;
    m_near = projnear;
    m_far = projfar;

    m_projection =
      glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

glm::mat4
lu::game::CameraComponent::getProjectionMatrix() const
{
    return m_projection;
}

glm::mat4
lu::game::CameraComponent::getViewMatrix() const
{
    return glm::translate(glm::mat4_cast(m_transform->getOrientation()),
                          m_transform->getPosition());
}

glm::vec3
lu::game::CameraComponent::getForwardVector() const
{
    return glm::vec3(0.0f, 0.0f, -1.0f) * m_transform->getOrientation();
}

glm::vec3
lu::game::CameraComponent::getLeftVector() const
{
    return glm::vec3(-1.0f, 0.0f, 0.0f) * m_transform->getOrientation();
}

void
lu::game::CameraComponent::updateTransform()
{
    // Get the first TransformComponent of our host
    m_transform =
      getHostComponentsOfType<TransformComponent>("TransformComponent").at(0);
}
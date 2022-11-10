#include "Game/Components/CameraComponent.h"

ce::game::CameraComponent::CameraComponent()
{
	glm::vec2 size = ce::core::Application::getScreenBufferSize();

	m_aspectRatio = (float)size.x / (float)size.y;
}

void ce::game::CameraComponent::init()
{
	bDrawable = false;
	bTickable = false;

	updateTransform();
}

void ce::game::CameraComponent::tick(float dt)
{
}

void ce::game::CameraComponent::draw(ce::graphics::Renderer3D* renderer)
{
}

std::string ce::game::CameraComponent::getType()
{
	return std::string("CameraComponent");
}

void ce::game::CameraComponent::setProjection(float fov, float aspectRatio, float projnear, float projfar)
{
	m_fov = fov;
	m_aspectRatio = aspectRatio;
	m_near = projnear;
	m_far = projfar;

	m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
}

glm::mat4 ce::game::CameraComponent::getProjectionMatrix() const
{
	return m_projection;
}

glm::mat4 ce::game::CameraComponent::getViewMatrix() const
{
	return glm::translate(glm::mat4_cast(m_transform->getOrientation()), m_transform->getPosition());
}

glm::vec3 ce::game::CameraComponent::getForwardVector() const
{
	return glm::vec3(0.0f, 0.0f, -1.0f) * m_transform->getOrientation();
}

glm::vec3 ce::game::CameraComponent::getLeftVector() const
{
	return glm::vec3(-1.0f, 0.0f, 0.0f) * m_transform->getOrientation();
}

void ce::game::CameraComponent::updateTransform()
{
	// Get the first TransformComponent of our host
	m_transform = getHostComponentsOfType<TransformComponent>("TransformComponent").at(0);
}
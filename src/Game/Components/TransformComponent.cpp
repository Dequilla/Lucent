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

glm::mat4 ce::game::TransformComponent::getAsModelMatrix()
{
	glm::quat orientX = glm::angleAxis(glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat orientY = glm::angleAxis(glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat orientZ = glm::angleAxis(glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::quat orientation = orientX * orientY * orientZ;
	glm::mat4 rot = glm::mat4_cast(orientation);

	glm::mat4 matrix;
	matrix = glm::translate(matrix, m_position);
	matrix = glm::scale(matrix, m_scale);
	matrix = matrix * rot;

	return matrix;
}

void ce::game::TransformComponent::pitch(float degrees)
{
	m_rotation.x += degrees;
}

void ce::game::TransformComponent::yaw(float degrees)
{
	m_rotation.y += degrees;
}

void ce::game::TransformComponent::roll(float degrees)
{
	m_rotation.z += degrees;
}

void ce::game::TransformComponent::rotate(float degX, float degY, float degZ)
{
	m_rotation += glm::vec3(degX, degY, degZ);
}

void ce::game::TransformComponent::rotate(glm::vec3 degrees)
{
	m_rotation += degrees;
}

void ce::game::TransformComponent::setRotation(float degX, float degY, float degZ)
{
	m_rotation = glm::vec3(degX, degY, degZ);
}

void ce::game::TransformComponent::setRotation(glm::vec3 degrees)
{
	m_rotation = degrees;
}

void ce::game::TransformComponent::move(float x, float y, float z)
{
	m_position += glm::vec3(x, y, z);
}

void ce::game::TransformComponent::move(glm::vec3 xyz)
{
	m_position += xyz;
}

void ce::game::TransformComponent::setPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}

void ce::game::TransformComponent::setPosition(glm::vec3 xyz)
{
	m_position = xyz;
}

void ce::game::TransformComponent::scale(float x, float y, float z)
{
	m_scale += glm::vec3(x, y, z);
}

void ce::game::TransformComponent::scale(glm::vec3 xyz)
{
	m_scale += xyz;
}

void ce::game::TransformComponent::setScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void ce::game::TransformComponent::setScale(glm::vec3 xyz)
{
	m_scale = xyz;
}
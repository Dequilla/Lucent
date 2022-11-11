#include "Game/GameObjects/CameraObject.h"

lu::game::CameraObject::CameraObject()
{
	this->addComponent(&m_cameraComponent);
	this->addComponent(&m_transformComponent);

	m_cameraComponent.updateTransform();
}
#include "Game/GameObjects/CameraObject.h"

ce::game::CameraObject::CameraObject()
{
	this->addComponent(&m_cameraComponent);
	this->addComponent(&m_transformComponent);

	m_cameraComponent.updateTransform();
}
#include "Game/GameObjects/ModelObject.h"

ce::game::ModelObject::ModelObject()
{
	this->addComponent(&m_transformComponent);
	this->addComponent(&m_modelComponent);

	m_modelComponent.updateTransform();
}
#include "LightObjects.h"

ce::game::DirLightObject::DirLightObject()
{
	this->addComponent(&m_light);
}

ce::game::PointLightObject::PointLightObject()
{
	this->addComponent(&m_light);
}

ce::game::SpotLightObject::SpotLightObject()
{
	this->addComponent(&m_light);
}
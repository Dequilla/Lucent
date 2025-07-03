#include "Game/GameObjects/LightObjects.h"

lu::game::DirLightObject::DirLightObject()
{
    this->addComponent(&m_light);
}

lu::game::PointLightObject::PointLightObject()
{
    this->addComponent(&m_light);
}

lu::game::SpotLightObject::SpotLightObject()
{
    this->addComponent(&m_light);
}
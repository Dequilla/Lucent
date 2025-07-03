#include "Game/GameObjects/ModelObject.h"

lu::game::ModelObject::ModelObject()
{
    this->addComponent(&m_transformComponent);
    this->addComponent(&m_modelComponent);

    m_modelComponent.updateTransform();
}
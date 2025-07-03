#pragma once

#include "Game/Components/ModelComponent.h"
#include "Game/Components/TransformComponent.h"
#include "Game/GameObject.h"

namespace lu
{
    namespace game
    {

        class ModelObject : public GameObject
        {
            protected:
                game::TransformComponent m_transformComponent;
                game::ModelComponent m_modelComponent;

            public:
                ModelObject();

                game::TransformComponent *transform()
                {
                    return &m_transformComponent;
                }

                game::ModelComponent *model() { return &m_modelComponent; }
        };

    }
}
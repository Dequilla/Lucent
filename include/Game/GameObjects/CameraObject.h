#pragma once

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"

#include "Game/GameObject.h"

#include "Game/Components/CameraComponent.h"
#include "Game/Components/TransformComponent.h"

namespace lu
{
    namespace game
    {

        class CameraObject : public GameObject
        {
                lu::game::TransformComponent m_transformComponent;
                lu::game::CameraComponent m_cameraComponent;

            public:
                CameraObject();

                game::CameraComponent *camera() { return &m_cameraComponent; }

                game::TransformComponent *transform()
                {
                    return &m_transformComponent;
                }
        };

    }
}
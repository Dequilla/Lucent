#pragma once

#include "Game/Components/LightComponents.h"
#include "Game/GameObject.h"

namespace lu
{
    namespace game
    {

        class DirLightObject : public GameObject
        {
                game::DirLightComponent m_light;

            public:
                DirLightObject();

                DirLightComponent *light() { return &m_light; }
        };

        class PointLightObject : public GameObject
        {
                game::PointLightComponent m_light;

            public:
                PointLightObject();

                PointLightComponent *light() { return &m_light; }
        };

        class SpotLightObject : public GameObject
        {
                game::SpotLightComponent m_light;

            public:
                SpotLightObject();

                SpotLightComponent *light() { return &m_light; }
        };

    }
}
#pragma once

#include "BaseComponent.h"
#include "Graphics/Lights.h"
#include "Graphics/Renderer/Renderer3D.h"

namespace lu
{
    namespace game
    {

        class DirLightComponent
          : public BaseComponent
          , public lu::graphics::DirLight
        {
            public:
                void init() override;

                void tick(float dt) override;
                void draw(lu::graphics::Renderer3D *renderer) override;

                std::string getType()
                {
                    return std::string("DirLightComponent");
                }
        };

        class PointLightComponent
          : public BaseComponent
          , public lu::graphics::PointLight
        {
            public:
                void init() override;

                void tick(float dt) override;
                void draw(lu::graphics::Renderer3D *renderer) override;

                std::string getType()
                {
                    return std::string("PointLightComponent");
                }
        };

        class SpotLightComponent
          : public BaseComponent
          , public lu::graphics::SpotLight
        {
            public:
                void init() override;

                void tick(float dt) override;
                void draw(lu::graphics::Renderer3D *renderer) override;

                std::string getType()
                {
                    return std::string("SpotLightComponent");
                }
        };

    }
}
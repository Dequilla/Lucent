#pragma once

#include "BaseComponent.h"

#include "Graphics/Transform.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/quaternion.hpp"

namespace lu
{
    namespace game
    {

        class TransformComponent
          : public BaseComponent
          , public lu::graphics::Transform
        {
            public:
                virtual void init() override;

                virtual void tick(float dt) override;
                virtual void draw(lu::graphics::Renderer3D *renderer) override;

                virtual std::string getType() override;
        };

    }
}
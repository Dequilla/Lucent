#pragma once

#include "Core/Application.h"

#include "BaseComponent.h"
#include "TransformComponent.h"

namespace lu
{
    namespace game
    {

        class CameraComponent : public BaseComponent
        {
            protected:
                TransformComponent *m_transform;

                float m_fov = 80.f;
                float m_near = 0.1f;
                float m_far = 100.f;
                float m_aspectRatio = 0.f;

                glm::mat4 m_projection;

            public:
                CameraComponent();

                virtual void init() override;
                virtual void tick(float dt) override;
                virtual void draw(lu::graphics::Renderer3D *renderer) override;

                virtual std::string getType() override;

                void setProjection(float fov,
                                   float aspectRatio,
                                   float projnear,
                                   float projfar);

                glm::mat4 getProjectionMatrix() const;
                glm::mat4 getViewMatrix() const;

                glm::vec3 getForwardVector() const;
                glm::vec3 getLeftVector() const;

                /**
                 * \brief Updates the transform component used
                 *
                 * If it cannot find one among it's hosts component list it will
                 * set it to a default position
                 */
                void updateTransform();
        };

    }
}
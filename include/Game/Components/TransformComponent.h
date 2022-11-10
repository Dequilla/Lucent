#pragma once

#include "BaseComponent.h"

#include "Graphics/Transform.h"

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"
#include "GLM/gtc/matrix_transform.hpp"

namespace ce { namespace game {

	class TransformComponent : public BaseComponent, public ce::graphics::Transform
	{
	public:
		virtual void init() override;

		virtual void tick(float dt) override;
		virtual void draw(ce::graphics::Renderer3D* renderer) override;

		virtual std::string getType() override;
	};

}}
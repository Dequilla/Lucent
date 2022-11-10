#pragma once

#include "BaseComponent.h"
#include "Graphics/Renderer/Renderer3D.h"
#include "Graphics/Lights.h"

namespace ce { namespace game {

	class DirLightComponent : public BaseComponent, public ce::graphics::DirLight
	{
	public:

		void init() override;

		void tick(float dt) override;
		void draw(ce::graphics::Renderer3D* renderer) override;

		std::string getType() { return std::string("DirLightComponent"); }
	};

	class PointLightComponent : public BaseComponent, public ce::graphics::PointLight
	{

	public:

		void init() override;

		void tick(float dt) override;
		void draw(ce::graphics::Renderer3D* renderer) override;

		std::string getType() { return std::string("PointLightComponent"); }
	};

	class SpotLightComponent : public BaseComponent, public ce::graphics::SpotLight
	{
	public:

		void init() override;

		void tick(float dt) override;
		void draw(ce::graphics::Renderer3D* renderer) override;

		std::string getType() { return std::string("SpotLightComponent"); }
	};

}}
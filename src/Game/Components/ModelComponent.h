#pragma once

#include "Game/Components/TransformComponent.h"
#include "Game/Components/BaseComponent.h"

#include "Graphics/Renderer/Renderer3D.h"
#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Model/Model.h"

namespace ce { namespace game {

	class ModelComponent : public BaseComponent
	{
	protected:
		ce::graphics::Model m_model;

	public:
		virtual void init() override;
		virtual void tick(float dt) override;
		virtual void draw(ce::graphics::Renderer3D* renderer) override;

		virtual std::string getType() override;

		void setModel(ce::graphics::Model model);
	};

}}
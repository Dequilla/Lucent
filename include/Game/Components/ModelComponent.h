#pragma once

#include "Game/Components/TransformComponent.h"
#include "Game/Components/BaseComponent.h"

#include "Graphics/Renderer/Renderer3D.h"
#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Model/Model.h"

namespace lu { namespace game {

	class ModelComponent : public BaseComponent
	{
	protected:
		lu::graphics::Model m_model;

		TransformComponent* m_transform;

	public:
		virtual void init() override;
		virtual void tick(float dt) override;
		virtual void draw(lu::graphics::Renderer3D* renderer) override;

		virtual std::string getType() override;

		void setModel(lu::graphics::Model model);
		
		/**
		* \brief Updates the transform component used
		*
		* If it cannot find one among it's hosts component list it will set it to a default position
		*/
		void updateTransform();
	};

}}
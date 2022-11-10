#pragma once

#include "Game/GameObject.h"
#include "Game/Components/TransformComponent.h"
#include "Game/Components/ModelComponent.h"

namespace ce { namespace game {

	class ModelObject : public GameObject
	{
	protected:
		game::TransformComponent	m_transformComponent;
		game::ModelComponent		m_modelComponent;

	public:
		ModelObject();

		game::TransformComponent*	transform() { return &m_transformComponent; }
		game::ModelComponent*		model() { return &m_modelComponent; }
	};

}}
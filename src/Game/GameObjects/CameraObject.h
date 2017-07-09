#pragma once

#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"

#include "Game/GameObject.h"

#include "Game/Components/TransformComponent.h"
#include "Game/Components/CameraComponent.h"

namespace ce { namespace game {

	class CameraObject : public GameObject
	{
		ce::game::TransformComponent	m_transformComponent;
		ce::game::CameraComponent		m_cameraComponent;

	public:
		CameraObject();

		game::CameraComponent* camera() { return &m_cameraComponent; }
		game::TransformComponent* transform() { return &m_transformComponent; }
	};

}}
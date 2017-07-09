#pragma once

#include "GLM/glm.hpp"

#include "GameMode.h"

#include "Graphics/Renderer/ForwardRenderer.h"
#include "Graphics/Model/ModelLoader.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Lights.h"

#include "Game/GameObject.h"
#include "Game/GameObjects/CameraObject.h"
#include "Game/GameObjects/ModelObject.h"
#include "Game/Components/TransformComponent.h"
#include "Game/Components/ModelComponent.h"

#include "Core/Application.h"

namespace ce { namespace game {

	class ExampleGameMode : public GameMode
	{
	protected:
		// GameObjects
		ce::game::ModelObject m_nanosuit;
		ce::game::ModelObject m_grassy;
		ce::game::CameraObject m_camera;

		ce::graphics::ForwardRenderer m_renderer;
		ce::graphics::LightSetup m_lights;

		// TODO: MovementComponent?
		bool m_moveForward = false;
		bool m_moveBackward = false;
		bool m_moveLeft = false;
		bool m_moveRight = false;

		float m_orientYaw = 0.0f;
		float m_orientPitch = 0.0f;

	public:
		virtual void init() override;
		virtual void begin() override;
		virtual void tick(float dt) override;
		virtual void draw() override;
		virtual void end() override;

		void cameraYaw(float axis);
		void cameraPitch(float axis);

		void moveLeft(bool pressed);
		void moveRight(bool pressed);
		void moveForward(bool pressed);
		void moveBackward(bool pressed);

		void movePLightF(bool pressed);
		void movePLightB(bool pressed);
		void movePLightL(bool pressed);
		void movePLightR(bool pressed);
	};

}}
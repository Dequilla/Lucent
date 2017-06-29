/**
* \file ForwardRenderer.h
*/
#pragma once

#include "Graphics/Renderer/Renderer3D.h"
#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Lights.h"
#include "Graphics/Camera.h"

#include "Graphics/Model/Mesh.h"

namespace ce { namespace graphics {

	class ForwardRenderer : public Renderer3D
	{
	private:
		Camera* m_camera;
		LightSetup m_lightSetup;

	public:
		void init() override;
		void begin() override;
		void beginScene(Camera* camera) override;
		void submit(const RenderCommand& command) override;
		void submitMesh(Mesh* mesh, const glm::mat4& transform) override;
		void submitLightSetup(const LightSetup& lightSetup) override;
		void endScene() override;
		void end() override;
		void present() override;
	};

}}
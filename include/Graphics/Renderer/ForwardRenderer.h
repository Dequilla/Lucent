/**
* \file ForwardRenderer.h
*/
#pragma once

#include "Graphics/Renderer/Renderer3D.h"
#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Lights.h"

#include "Graphics/Model/Mesh.h"

namespace lu { namespace graphics {

	class ForwardRenderer : public Renderer3D
	{
	private:
		glm::mat4 m_viewMatrix;
		glm::mat4 m_projectionMatrix;
		LightSetup m_lightSetup;

	public:
		void init() override;
		void begin() override;
		void beginScene(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;
		void submit(const RenderCommand& command) override;
		void submitMesh(Mesh* mesh, const glm::mat4& transform) override;
		void submitLightSetup(const LightSetup& lightSetup) override;
		void submitDirLight(const DirLight& light) override;
		void submitPointLight(const PointLight& light) override;
		void submitSpotLight(const SpotLight& light) override;
		void endScene() override;
		void end() override;
		void present() override;
	};

}}
#pragma once

#include "Core/Application.h"

#include "Graphics/Renderer3D.h"

namespace ce { namespace graphics {

	class ForwardRenderer : public Renderer3D
	{
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::vec3 m_cameraPosition;

		LightSetup m_lights;

	public:
		ForwardRenderer(); // Default
		ForwardRenderer(unsigned int width, unsigned int height); // Initialize with screen buffer size

		void init() override;
		void begin() override;
		void beginScene(Camera* camera) override;
		void submit(const RenderCommand& command) override;
		void submitMesh(Mesh* mesh, const glm::mat4& transform) override;
		void submitLightSetup(LightSetup& setup) override;
		void endScene() override;
		void end() override;

		virtual void present() override;
	};

}}
#pragma once

#include "Graphics/Model/Mesh.h"

#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Lights.h"
#include "Graphics/Camera.h"

#include "GLM/glm.hpp"

#include <vector>

namespace ce { namespace graphics {

	typedef std::vector<RenderCommand> CommandQueue;


	//
	// 3D renderer base class
	//
	// Implemented as:
	//	- ForwardRenderer
	//
	class Renderer3D
	{
	protected:
		unsigned int m_screenBufferWidth, m_screenBufferHeight;

		CommandQueue m_commandQueue;

	public:
		virtual void init() = 0;
		virtual void begin() = 0;
		virtual void beginScene(Camera* camera) = 0;
		virtual void submit(const RenderCommand& command) = 0;
		virtual void submitMesh(Mesh* mesh, const glm::mat4& transform) = 0;
		virtual void submitLightSetup(const LightSetup& lightSetup) = 0;
		virtual void endScene() = 0;
		virtual void end() = 0;
		virtual void present() = 0;

		virtual void setScreenBufferSize(unsigned int width, unsigned int height) { m_screenBufferWidth = width; m_screenBufferHeight = height; }
	};

}}
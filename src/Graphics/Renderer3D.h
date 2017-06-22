#pragma once

#include <vector>

#include "Camera.h"
#include "LightSetup.h"
#include "RenderCommand.h"

namespace ce { namespace graphics { 

	typedef std::vector<RenderCommand> CommandQueue;

	//
	// Renderer3D base class
	//
	class Renderer3D
	{
	protected:
		unsigned int m_screenBufferWidth, m_screenBufferHeight;

		CommandQueue m_commandQueue;

	public:
		virtual ~Renderer3D() {}

		virtual void init() = 0;
		virtual void begin() = 0;
		virtual void beginScene(Camera* camera) = 0;
		virtual void submit(const RenderCommand& command) = 0;
		virtual void submitMesh(Mesh* mesh, const glm::mat4& transform) = 0;
		virtual void submitLightSetup(LightSetup& setup) = 0;
		virtual void endScene() = 0;
		virtual void end() = 0;

		virtual void present() = 0; 

		virtual void setScreenBufferSize(unsigned int width, unsigned int height) { m_screenBufferWidth = width; m_screenBufferHeight = height; }
	};

}}
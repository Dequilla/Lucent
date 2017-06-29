/**
* \file Renderer3D.h
*/
#pragma once

#include "Graphics/Model/Mesh.h"

#include "Graphics/Renderer/RenderCommand.h"

#include "Graphics/Lights.h"
#include "Graphics/Camera.h"

#include "GLM/glm.hpp"

#include <vector>

namespace ce { namespace graphics {

	typedef std::vector<RenderCommand> CommandQueue; /**< The queue type of which we store the render commands */

	/**
	* \breif The base class for all 3D renderers
	*
	* Implementations:
	*	-	ForwardRenderer
	*/
	class Renderer3D
	{
	protected:
		unsigned int m_screenBufferWidth, m_screenBufferHeight; /**< The size of the screenbuffer we draw too */

		CommandQueue m_commandQueue; /**< The command queue where we store the render commands */

	public:
		virtual void init() = 0;						/**< Initialization stage of the renderer */
		virtual void begin() = 0;						/**< Begining stage of the renderer */
		virtual void beginScene(Camera* camera) = 0;	/**< Begining of the scene */
		virtual void submit(const RenderCommand& command) = 0;					/**< Submit a render command */
		virtual void submitMesh(Mesh* mesh, const glm::mat4& transform) = 0;	/**< Submit a lone mesh */
		virtual void submitLightSetup(const LightSetup& lightSetup) = 0;		/**< Submit the light setup to use */
		virtual void endScene() = 0;	/**< Scene ending */
		virtual void end() = 0;			/**< Render loop ending */
		virtual void present() = 0;		/**< Do the actual rendering and present it on screen */

		/**
		* \brief Set the screen buffer size
		*
		* Essentially setting the viewport
		*
		* @param width The width in pixels of the window
		* @param height The height in pixels of the window
		*/
		virtual void setScreenBufferSize(unsigned int width, unsigned int height) { m_screenBufferWidth = width; m_screenBufferHeight = height; }
	};

}}
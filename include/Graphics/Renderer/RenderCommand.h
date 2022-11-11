/**
* \file RenderCommand.h
*/
#pragma once

#include "Graphics/Model/Mesh.h"

#include "GLM/glm.hpp"

#include <vector>

namespace lu { namespace graphics {

	/**
	* \brief A structure of a rendercommand to be sent to a renderer
	*/
	struct RenderCommand
	{
		Mesh* mesh;
		glm::mat4 transform;
		Shader shader;
	};

}}
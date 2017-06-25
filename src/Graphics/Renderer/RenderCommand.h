#pragma once

#include "Graphics/Model/Mesh.h"

#include "GLM/glm.hpp"

#include <vector>

namespace ce { namespace graphics {

	struct RenderCommand
	{
		Mesh* mesh;
		glm::mat4 transform;
		Shader* shader;
	};

}}
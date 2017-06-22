#pragma once

#include "Graphics/Mesh.h"

#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	struct RendererUniform
	{
		std::string uniform;
	};

	struct RenderCommand
	{
		Mesh* mesh;
		glm::mat4 transform;
		Shader* shader;
		std::vector<RendererUniform> uniforms;
	};

}}
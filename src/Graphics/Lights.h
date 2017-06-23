#pragma once

#include "GLM/glm.hpp"

namespace ce { namespace graphics {

	class BaseLight
	{
	public:
		glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::vec3 specular = glm::vec3(0.6f, 0.6f, 0.6f);
	};

	class DirLight : public BaseLight
	{
	public:
		glm::vec3 direction = glm::vec3(-0.5f, -0.5f, -0.5f);
	};

	class PointLight : public BaseLight
	{
	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;
	};

	class SpotLight : public BaseLight
	{
	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;

		float cutOff = 0.96f;
		float outerCutOff = 0.90f;
	};

}}
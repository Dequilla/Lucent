#include "ShaderManager.h"

void ce::graphics::ShaderManager::addShader(std::string id, Shader shader)
{
	m_shaders.emplace(id, shader);
}

ce::graphics::Shader ce::graphics::ShaderManager::getShader(std::string id)
{
	return m_shaders.at(id);
}

void ce::graphics::ShaderManager::removeShader(std::string id)
{
	m_shaders.erase(id);
}
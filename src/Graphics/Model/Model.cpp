#include "Graphics/Model/Model.h"

lu::graphics::Model::Model(std::vector<std::shared_ptr<Mesh>> meshes)
{
	m_meshes = meshes;
}

void lu::graphics::Model::draw()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].get()->draw();
}

void lu::graphics::Model::draw(Renderer3D* renderer, glm::mat4 modelMatrix)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		RenderCommand command;
		command.mesh = m_meshes[i].get();
		command.shader = m_meshes[i].get()->material.shader;
		command.transform = modelMatrix;

		renderer->submit(command);
	}
}
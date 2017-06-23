#include "Model.h"

ce::graphics::Model::Model(std::vector<std::shared_ptr<Mesh>> meshes)
{
	m_meshes = meshes;
}

void ce::graphics::Model::draw()
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
		m_meshes[i].get()->draw();
}
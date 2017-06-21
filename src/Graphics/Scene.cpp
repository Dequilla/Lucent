#include "Scene.h"

ce::graphics::Scene::Scene()
{
}

void ce::graphics::Scene::addModel(Model model)
{
	m_models.push_back(model);
}

void ce::graphics::Scene::addDirLight(DirLight light)
{
	m_dirLights.push_back(light);
}

void ce::graphics::Scene::addPointLight(PointLight light)
{
	m_pointLights.push_back(light);
}

void ce::graphics::Scene::addSpotLight(SpotLight light)
{
	m_spotLights.push_back(light);
}

void ce::graphics::Scene::draw(Camera camera)
{
	m_shader.use();

	// TODO: temp, actually part of material
	m_shader.setFloat("material.shininess", 32.f);

	// TODO: can optimize
	glm::mat4 viewMatrix = camera.getViewMatrix();
	glm::mat4 projMatrix = camera.getProjectionMatrix();

	m_shader.setMat4("view", viewMatrix);
	m_shader.setMat4("projection", projMatrix);

	for (int i = 0; i < m_dirLights.size(); i++)
	{
		std::string number = std::to_string(i);

		m_shader.setVec3("dirLights[" + number + "].direction", m_dirLights[i].direction);

		m_shader.setVec3("dirLights[" + number + "].ambient", m_dirLights[i].ambient);
		m_shader.setVec3("dirLights[" + number + "].diffuse", m_dirLights[i].diffuse);
		m_shader.setVec3("dirLights[" + number + "].specular", m_dirLights[i].specular);
	}

	for (int i = 0; i < m_pointLights.size(); i++)
	{
		std::string number = std::to_string(i);

		m_shader.setVec3("pointLights[" + number + "].position", m_pointLights[i].position);

		m_shader.setVec3("pointLights[" + number + "].ambient", m_pointLights[i].ambient);
		m_shader.setVec3("pointLights[" + number + "].diffuse", m_pointLights[i].diffuse);
		m_shader.setVec3("pointLights[" + number + "].specular", m_pointLights[i].specular);

		m_shader.setFloat("pointLights[" + number + "].constant", m_pointLights[i].constant);
		m_shader.setFloat("pointLights[" + number + "].linear", m_pointLights[i].linear);
		m_shader.setFloat("pointLights[" + number + "].quadratic", m_pointLights[i].quadratic);
	}

	for (int i = 0; i < m_spotLights.size(); i++)
	{
		std::string number = std::to_string(i);

		m_shader.setVec3("spotLights[" + number + "].position", m_spotLights[i].position);
		m_shader.setVec3("spotLights[" + number + "].direction", m_spotLights[i].direction);

		m_shader.setVec3("spotLights[" + number + "].ambient", m_spotLights[i].ambient);
		m_shader.setVec3("spotLights[" + number + "].diffuse", m_spotLights[i].diffuse);
		m_shader.setVec3("spotLights[" + number + "].specular", m_spotLights[i].specular);

		m_shader.setFloat("spotLights[" + number + "].constant", m_spotLights[i].constant);
		m_shader.setFloat("spotLights[" + number + "].linear", m_spotLights[i].linear);
		m_shader.setFloat("spotLights[" + number + "].quadratic", m_spotLights[i].quadratic);
	}

	for (int i = 0; i < m_models.size(); i++)
	{
		m_models[i].draw(m_shader);
	}
}
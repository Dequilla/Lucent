#include "Scene.h"

ce::game::RootObject* ce::game::Scene::getRootObject()
{
	return &m_rootObject;
}

ce::game::GameObject* ce::game::Scene::getGameObjectByName(std::string name)
{
	return m_rootObject.getGameObjectByName(name);
}

void ce::game::Scene::init()
{
	m_rootObject.init(); // Initializes all the objects
}

void ce::game::Scene::begin()
{
}

void ce::game::Scene::tick(float dt)
{
	m_rootObject.tick(dt);
}

void ce::game::Scene::draw(ce::graphics::Renderer3D* renderer)
{
	m_rootObject.draw(renderer);
}

void ce::game::Scene::end()
{
}
#include "Game/Scene.h"

ce::game::RootObject* ce::game::Scene::getRootObject()
{
	return &m_rootObject;
}

ce::game::GameObject* ce::game::Scene::getGameObjectByName(std::string name)
{
	return m_rootObject.getGameObjectByName(name);
}

ce::game::GameObject* ce::game::Scene::addGameObject(std::string nameOfParent, GameObject * object)
{
	// If it matches the root object
	if (this->m_rootObject.name == nameOfParent)
	{
		return this->m_rootObject.addChild(object);
	}

	// If not root, go through all objects and check for the parent, then add it, then return
	return m_rootObject.getGameObjectByName(nameOfParent)->addChild(object);;
}

void ce::game::Scene::init()
{
	m_rootObject.name = "root";
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
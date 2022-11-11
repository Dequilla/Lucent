#include "Game/Scene.h"

lu::game::RootObject* lu::game::Scene::getRootObject()
{
	return &m_rootObject;
}

lu::game::GameObject* lu::game::Scene::getGameObjectByName(std::string name)
{
	return m_rootObject.getGameObjectByName(name);
}

lu::game::GameObject* lu::game::Scene::addGameObject(std::string nameOfParent, GameObject * object)
{
	// If it matches the root object
	if (this->m_rootObject.name == nameOfParent)
	{
		return this->m_rootObject.addChild(object);
	}

	// If not root, go through all objects and check for the parent, then add it, then return
	return m_rootObject.getGameObjectByName(nameOfParent)->addChild(object);;
}

void lu::game::Scene::init()
{
	m_rootObject.name = "root";
	m_rootObject.init(); // Initializes all the objects
}

void lu::game::Scene::begin()
{
}

void lu::game::Scene::tick(float dt)
{
	m_rootObject.tick(dt);
}

void lu::game::Scene::draw(lu::graphics::Renderer3D* renderer)
{
	m_rootObject.draw(renderer);
}

void lu::game::Scene::end()
{
}
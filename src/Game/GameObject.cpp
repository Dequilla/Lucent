#include "GameObject.h"

ce::game::GameObject::GameObject(GameObject* parent)
{
	m_parent = parent;
}

ce::game::GameObject::GameObject(GameObject* parent, std::string name)
{
	this->name = name;
	m_parent = parent;
}

ce::game::GameObject* ce::game::GameObject::addChild(GameObject child)
{
	child.setParent(this);
	m_children.push_back(child);

	return &m_children.back();
}

void ce::game::GameObject::setParent(GameObject* parent)
{
	m_parent = parent;
}

void ce::game::GameObject::removeChild(std::string name)
{
	for (int i = 0; i < m_children.size(); i++)
	{
		if (m_children[i].name == name)
		{
			m_children.erase(m_children.begin() + i);
		}
	}
}

void ce::game::GameObject::removeObject(std::string name)
{
	for (int i = 0; i < m_children.size(); i++)
	{
		// Check if names are equal
		if (m_children[i].name == name)
		{
			m_children.erase(m_children.begin() + i);
			return; 
		}
		else
		{
			// Check the children of this game object
			m_children[i].removeObject(name);
		}
	}
}

void ce::game::GameObject::tick(float dt)
{
	// Tick if tickable
	for (int i = 0; i < m_components.size(); i++)
	{
		if(m_components[i]->bTickable)
			m_components[i]->tick(dt);
	}

	// Tick children
	for (int i = 0; i < m_children.size(); i++) 
	{
		m_children[i].tick(dt);
	}
}

void ce::game::GameObject::draw(ce::graphics::Renderer3D* renderer)
{
	// Draw if drawable
	for (int i = 0; i < m_components.size(); i++)
	{
		if (m_components[i]->bDrawable)
			m_components[i]->draw(renderer);
	}

	// Draw children
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i].draw(renderer);
	}
}

ce::game::GameObject* ce::game::GameObject::getGameObjectByName(std::string name)
{
	for (int i = 0; i < m_children.size(); i++)
	{
		// Check if names are equal
		if (m_children[i].name == name)
		{
			return &m_children[i];
		}
		else
		{
			// Check the children of this game object
			return m_children[i].getGameObjectByName(name);
		}
	}

	return nullptr;
}

void ce::game::GameObject::addComponent(ce::game::BaseComponent* component)
{
	component->m_hostComponents = &m_components;
	m_components.push_back(component);
}

void ce::game::GameObject::init()
{
	// Init all components
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->init();
	}

	// Do the same for all the children
	for (int i = 0; i < m_children.size(); i++)
	{
		m_children[i].init();
	}
}
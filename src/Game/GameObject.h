#pragma once

#include <vector>
#include <string>

#include "Graphics/Renderer/Renderer3D.h"
#include "Game/Components/BaseComponent.h"

namespace ce { namespace game {

	class GameObject
	{
	protected:
		std::vector<GameObject> m_children;
		GameObject* m_parent = nullptr;			  // Also have parent's components creating recursion?
												  // Only problem: GameObjects inside GameObjects being positioned based on its parent
		std::vector<BaseComponent*> m_components; // TODO: Give pointer of this to components so all components can access its hosts(game objects) components (eg: modelComps can access transforComps)
												  // And we avoid circular dependencies
	public:
		/**
		* \brief Default constructor is only used by the root object
		*
		* Note if used by a gameobject a parent has to be set
		*/
		GameObject() {}
		GameObject(GameObject* parent);
		GameObject(GameObject* parent, std::string name);

		void setParent(GameObject* parent);

		void addChild(GameObject child);

		/**
		* \breif Remove this objects child with name
		*
		* Does not affect this objects children
		*
		* @param name The name of the object
		*/
		void removeChild(std::string name);

		/**
		* \brief Recursive function that finds the object with name and removes it
		*
		* Also checks the children.
		*
		* @param name The name of the desired object
		*/
		void removeObject(std::string name);

		/**
		* \breif Ticks itself and its children
		*
		* @param dt Delta time
		*/
		void tick(float dt);

		/**
		* \brief Draws itself and its children
		*
		* @param renderer A 3D renderer
		*/
		void draw(ce::graphics::Renderer3D* renderer);

		/**
		* \brief This GameObjects identifier
		*/
		std::string name;

		/**
		* \brief Find a object with the name
		*
		* It looks through it's children to find one with the matching name, if it can't find it
		* it checks their children and so on.
		*
		* @param name The name of the object to look for
		* @return Pointer to that game object, or nullptr if it can't be found
		*/
		GameObject* getGameObjectByName(std::string name);

		void addComponent(BaseComponent* component);

		void init();

		/**
		* \brief Get all components of the type specified
		*
		* T needs to be the component type you are trying to get
		*
		* @param type Type string as represented by a components getType() function
		* @return A component of the type specified, nullptr if none exist
		*/
		template<class T>
		std::vector<T*> getComponentsOfType(std::string type);
	};

	template<class T>
	inline std::vector<T*> ce::game::GameObject::getComponentsOfType(std::string type)
	{
		int count = 0;
		std::vector<T*> result;

		for (int i = 0; i < m_components.size(); i++)
		{
			if (type == m_components.at(i)->getType())
			{
				result.push_back(dynamic_cast<T*>(m_components.at(i)));
				count++;
			}
		}

		if (count < 1)
			result.push_back(nullptr);

		return result;
	}

	class RootObject : public GameObject
	{
	public:
		RootObject() : GameObject() {};
		RootObject(GameObject* parent) = delete;
		RootObject(GameObject* parent, std::string name) = delete;
	};
}}
#pragma once

#include <vector>

#include "Graphics/Renderer/Renderer3D.h"

namespace ce { namespace game {

	class BaseComponent
	{
	protected:
		friend class GameObject;

		/**
		* \brief Components of this components host(GameObject)
		*
		* Used to access other components on an object such as TransformComponents etc
		*/
		std::vector<BaseComponent*>* m_hostComponents;

	public:
		virtual ~BaseComponent() {};

		bool bTickable = false;
		bool bDrawable = false;

		virtual void init() = 0;

		virtual void tick(float dt) = 0;
		virtual void draw(ce::graphics::Renderer3D* renderer) = 0;

		/**
		* \brief Returns the type of Component in a string value
		*
		* Example: Model, Transform etc
		*/
		virtual std::string getType() = 0;

		/**
		* \breif Retrieve all the components of a type from the host
		*
		* T needs to be the class you are getting as a type as it converts it to that type
		*/
		template<class T>
		std::vector<T*> getHostComponentsOfType(std::string type);
	};

	template<class T>
	inline std::vector<T*> ce::game::BaseComponent::getHostComponentsOfType(std::string type)
	{
		std::vector<T*> result;

		for (int i = 0; i < m_hostComponents->size(); i++)
		{
			if (type == m_hostComponents->at(i)->getType())
			{
				result.push_back(dynamic_cast<T*>(m_hostComponents->at(i)));
			}
		}

		return result;
	}

}}
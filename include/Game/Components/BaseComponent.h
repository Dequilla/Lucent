#pragma once

#include <vector>

#include "Graphics/Renderer/Renderer3D.h"

namespace lu { namespace game {

	class BaseComponent
	{
	protected:
		friend class GameObject;

		/**
		* \brief Components of this components host(GameObject)
		*
		* Used to access other components on the host object such as TransformComponents etc
		* Since it is a pointer, if the host components change, it is updated here too
		*/
		std::vector<BaseComponent*>* m_hostComponents;

	public:
		virtual ~BaseComponent() {};

		bool bTickable = false;
		bool bDrawable = false;

		virtual void init() = 0;

		virtual void tick(float dt) = 0;
		virtual void draw(lu::graphics::Renderer3D* renderer) = 0;

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
		* Returns a vector with the first element being a nullptr if it can't find any
		*/
		template<class T>
		std::vector<T*> getHostComponentsOfType(std::string type);
	};

	template<class T>
	inline std::vector<T*> lu::game::BaseComponent::getHostComponentsOfType(std::string type)
	{
		int count = 0;
		std::vector<T*> result;

		for (unsigned int i = 0; i < m_hostComponents->size(); i++)
		{
			if (type == m_hostComponents->at(i)->getType())
			{
				result.push_back(dynamic_cast<T*>(m_hostComponents->at(i)));
				count++;
			}
		}

		if (count < 1)
			result.push_back(nullptr);

		return result;
	}

}}
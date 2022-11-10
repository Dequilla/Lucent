/**
* \file Model.h
*/
#pragma once

#include <memory>

#include "Graphics/Model/Mesh.h"

#include "Graphics/Renderer/ForwardRenderer.h"
#include "Graphics/Renderer/RenderCommand.h"

namespace ce { namespace graphics {

	/**
	* \brief A model object
	* 
	* Contains pointers to the meshes it is built of
	* To load use the ModelLoader class
	*/
	class Model
	{
	protected:
		friend class ModelLoader;

		std::string m_directory;

		std::vector<std::shared_ptr<Mesh>> m_meshes;

	public:
		Model() {}

		/**
		* \brief Construct model from a set of meshes
		*/
		Model(std::vector<std::shared_ptr<Mesh>> meshes);

		/**
		* \brief old draw function to be replaced
		*/
		void draw();

		/**
		* \brief old draw function to be replaced
		*/
		void draw(Renderer3D* renderer, glm::mat4 modelMatrix);
	};

}}
#pragma once

#include <memory>

#include "Graphics/Model/Mesh.h"

namespace ce { namespace graphics {

	//
	// Model
	//  - Contains pointers to the meshes it uses
	//  - Use modelLoader to load
	class Model
	{
	protected:
		friend class ModelLoader;

		std::string m_directory;

		// TODO: Remember to properly move the constructed pointer or we will have two shared_ptrs and memory wont be released
		std::vector<std::shared_ptr<Mesh>> m_meshes;

	public:
		Model() {}
		Model(std::vector<std::shared_ptr<Mesh>> meshes);

		// TODO: TEMP FOR TESTING
		void draw();
	};

}}
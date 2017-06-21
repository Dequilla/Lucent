#pragma once

#include <vector>

#include "Graphics/Model.h"
#include "Graphics/Lights.h"
#include "Graphics/Camera.h"

#include "Core/Window.h"
#include "Core/Application.h"

namespace ce { namespace graphics {

	class Scene
	{
	private:
		std::vector<Model> m_models;

		std::vector<DirLight> m_dirLights;
		std::vector<PointLight> m_pointLights;
		std::vector<SpotLight> m_spotLights;
		
		// For now one shader
		Shader m_shader = Shader("Shaders/opaque_sd_vertex.glsl", "Shaders/opaque_sd_fragment.glsl");

	protected:
	public:
		
		Scene();

		void addModel(Model model);

		void addDirLight(DirLight light);
		void addPointLight(PointLight light);
		void addSpotLight(SpotLight light);

		void draw(Camera camera);
	};

} }
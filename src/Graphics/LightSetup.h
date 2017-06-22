#pragma once

#include <vector>

#include "Graphics/Lights.h"

namespace ce { namespace graphics { 

	class LightSetup
	{
		// TODO
	private:
		std::vector<DirLight*> m_directionalLights;
		std::vector<PointLight*> m_pointLights;
		std::vector<SpotLight*> m_spotLights;

	public:
		LightSetup();
		~LightSetup();

		DirLight* addDirLight(DirLight* dirLight);
		void removeDirLight(DirLight* dirLight);

		PointLight* addPointLight(PointLight* pointLight);
		void removePointLight(PointLight* pointLight);

		SpotLight* addSpotLight(SpotLight* spotLight);
		void removeSpotLight(SpotLight* spotLight);
	};

}}
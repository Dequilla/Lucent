#include "LightSetup.h"

ce::graphics::LightSetup::LightSetup()
{
}

ce::graphics::LightSetup::~LightSetup()
{
}

ce::graphics::DirLight* ce::graphics::LightSetup::addDirLight(DirLight* dirLight)
{
	m_directionalLights.push_back(dirLight);
	return dirLight;
}

void ce::graphics::LightSetup::removeDirLight(DirLight * dirLight)
{
	for (int i = 0; i < m_directionalLights.size(); i++)
	{
		if (m_directionalLights[i] == dirLight)
		{
			m_directionalLights.erase(m_directionalLights.begin() + i);
			break;
		}
	}
}

ce::graphics::PointLight* ce::graphics::LightSetup::addPointLight(PointLight* pointLight)
{
	m_pointLights.push_back(pointLight);
	return pointLight;
}

void ce::graphics::LightSetup::removePointLight(PointLight* pointLight)
{
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		if (m_pointLights[i] == pointLight)
		{
			m_pointLights.erase(m_pointLights.begin() + i);
			break;
		}
	}
}

ce::graphics::SpotLight* ce::graphics::LightSetup::addSpotLight(SpotLight* spotLight)
{
	m_spotLights.push_back(spotLight);
	return spotLight;
}

void ce::graphics::LightSetup::removeSpotLight(SpotLight* spotLight)
{
	for (int i = 0; i < m_spotLights.size(); i++)
	{
		if (m_spotLights[i] == spotLight)
		{
			m_spotLights.erase(m_spotLights.begin() + i);
			break;
		}
	}
}
#pragma once

#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Shader;

class LightingModule
{
private:
	shared_ptr<DirectionalLight> m_directionalLight;
	std::vector<shared_ptr<PointLight>> m_pointLights;
	shared_ptr<SpotLight> m_spotLight;
public:

	shared_ptr<DirectionalLight> SetDirectionalLight(shared_ptr<DirectionalLight> light) {return m_directionalLight = light; }
	shared_ptr<DirectionalLight> SetDirectionalLight(glm::vec3 direction, LightColorData data) {return m_directionalLight = make_shared<DirectionalLight>(direction, data); }
	shared_ptr<PointLight> GetDirectionalLight() { m_directionalLight; }

	shared_ptr<PointLight> AddPointLight(shared_ptr<PointLight> light);
	shared_ptr<PointLight> AddPointLight(glm::vec3 position, LightColorData colorData, LightAttenuationData attentuationData);
	shared_ptr<PointLight> GetPointLight(int index) { return m_pointLights.size() > index ? m_pointLights[index] : nullptr; }

	shared_ptr<SpotLight> SetSpotLight(shared_ptr<SpotLight> light);
	shared_ptr<SpotLight> SetSpotLight(glm::vec3 position, glm::vec3 dir, LightColorData colorData, LightAttenuationData attentuationData, float cutoff, float outerCutoff);
	shared_ptr<PointLight> GetSpotLight() { m_spotLight; }

	void SetShaderLightingData(Shader* pShader);
};


#include "LightingModule.h"

#include "Shader.h"

shared_ptr<PointLight> LightingModule::AddPointLight(shared_ptr<PointLight> light)
{
    m_pointLights.push_back(light);
    return light;
}

shared_ptr<PointLight> LightingModule::AddPointLight(glm::vec3 position, LightColorData colorData, LightAttenuationData attentuationData)
{
    m_pointLights.emplace_back(make_shared<PointLight>(position, colorData, attentuationData));
    return m_pointLights[m_pointLights.size() - 1];
}

shared_ptr<SpotLight> LightingModule::SetSpotLight(shared_ptr<SpotLight> light)
{
    return m_spotLight = light;
}

shared_ptr<SpotLight> LightingModule::SetSpotLight(glm::vec3 position, glm::vec3 dir, LightColorData colorData, LightAttenuationData attentuationData, float cutoff, float outerCutoff)
{
    return m_spotLight = make_shared<SpotLight>(position, dir, colorData, attentuationData, cutoff, outerCutoff);
}

void LightingModule::SetShaderLightingData(Shader* pShader)
{
    pShader->Use();

    if (m_directionalLight != nullptr)
    {
        m_directionalLight->SetShaderLightData(pShader);
    }

    pShader->SetInt("uPointLightCount", m_pointLights.size() - 1);
    for (int i = 0; i < m_pointLights.size(); i++)
    {
        if (m_pointLights[i] != nullptr)
            m_pointLights[i]->SetShaderLightData(pShader, i);
    }

    if (m_spotLight != nullptr)
    {
        m_spotLight->SetShaderLightData(pShader, 0);
    }
}

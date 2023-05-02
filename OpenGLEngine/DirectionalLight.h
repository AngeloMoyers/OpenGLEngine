#pragma once
#include "Light.h"

class Shader;

class DirectionalLight :
    public Light
{
private:
    glm::vec3 m_lightDirection;
public:
    DirectionalLight(glm::vec3 lightDirection, LightColorData data)
        :m_lightDirection{ lightDirection }
    {
        m_lightColorData = data;
    };

    void SetShaderLightData(Shader* pShader);
};


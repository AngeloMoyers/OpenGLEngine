#pragma once
#include "Light.h"


class Shader;

class PointLight :
    public Light
{
private:
    glm::vec3 m_position;
    LightAttenuationData m_attenuationData;
public:
    PointLight(glm::vec3 position, LightColorData colorData, LightAttenuationData attentuationData)
        :Light(position)
        ,m_position{ position }
    {
        m_lightColorData = colorData;
        m_attenuationData = attentuationData;
    };

    void SetShaderLightData(Shader* pShader, int count);

    void UpdateTransform(glm::vec3 pos) { m_position = pos;}
};


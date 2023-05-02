#pragma once
#include "Light.h"

class Shader;

class SpotLight :
    public Light
{
private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    LightAttenuationData m_attenuationData;
    float m_edgeCutoff;
    float m_outerEdgeCutoff;
public:
    SpotLight(glm::vec3 position, glm::vec3 dir, LightColorData colorData, LightAttenuationData attentuationData, float cutoff, float outerCutoff)
        :m_position{ position }
        ,m_direction{ dir }
        ,m_edgeCutoff{ glm::cos(glm::radians(cutoff)) }
        ,m_outerEdgeCutoff{ glm::cos(glm::radians(outerCutoff)) }

    {
        m_lightColorData = colorData;
        m_attenuationData = attentuationData;
    };

    void SetShaderLightData(Shader* pShader, int count);

    void UpdateTransform(glm::vec3 pos, glm::vec3 f) { m_position = pos; m_direction = f; }
};



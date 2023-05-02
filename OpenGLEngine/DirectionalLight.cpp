#include "DirectionalLight.h"

#include "Shader.h"

void DirectionalLight::SetShaderLightData(Shader* pShader)
{
	if (pShader == nullptr) return;
	pShader->SetVec3("uDLight.direction", m_lightDirection);
	pShader->SetVec3("uDLight.ambient", m_lightColorData.ambient);
	pShader->SetVec3("uDLight.diffuse", m_lightColorData.diffuse);
	pShader->SetVec3("uDLight.specular", m_lightColorData.specular);
}

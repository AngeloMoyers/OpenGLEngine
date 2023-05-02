#include "SpotLight.h"

#include "Shader.h"

void SpotLight::SetShaderLightData(Shader* pShader, int count)
{
	pShader->SetVec3("uSLight.position", m_position);
	pShader->SetVec3("uSLight.direction", m_direction);
	pShader->SetFloat("uSLight.cutoff", m_edgeCutoff);
	pShader->SetFloat("uSLight.outerCutoff", m_outerEdgeCutoff);

	pShader->SetVec3("uSLight.ambient", m_lightColorData.ambient);
	pShader->SetVec3("uSLight.diffuse", m_lightColorData.diffuse);
	pShader->SetVec3("uSLight.specular", m_lightColorData.specular);
	pShader->SetFloat("uSLight.constant", m_attenuationData.constant);
	pShader->SetFloat("uSLight.linear", m_attenuationData.linear);
	pShader->SetFloat("uSLight.quadratic", m_attenuationData.quadratic);
}

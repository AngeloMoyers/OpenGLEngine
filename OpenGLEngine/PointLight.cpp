#include "PointLight.h"

#include "Shader.h"

#include <string>

void PointLight::SetShaderLightData(Shader* pShader, int count)
{
	std::string shaderVarName = "uPLight[" + count + ']';

	pShader->SetVec3(shaderVarName + ".position", m_position);
	pShader->SetVec3(shaderVarName + ".ambient", m_lightColorData.ambient);
	pShader->SetVec3(shaderVarName + ".diffuse", m_lightColorData.diffuse);
	pShader->SetVec3(shaderVarName + ".specular", m_lightColorData.specular);
	pShader->SetFloat(shaderVarName + ".constant", m_attenuationData.constant);
	pShader->SetFloat(shaderVarName + ".linear", m_attenuationData.linear);
	pShader->SetFloat(shaderVarName + ".quadratic", m_attenuationData.quadratic);
}

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GameObject.h"

struct LightColorData
{
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct LightAttenuationData
{
	float constant;
	float linear;
	float quadratic;
};

class Light : public GameObject
{
protected:
	LightColorData m_lightColorData;

public:
	Light()
		:GameObject(glm::vec3(0, 0, 0))
	{};
	Light(glm::vec3 pos)
		:GameObject(pos)
	{};
};


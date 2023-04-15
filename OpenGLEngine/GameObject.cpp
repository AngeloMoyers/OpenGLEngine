#include "GameObject.h"

GameObject::GameObject()
	:m_position(glm::vec3(0,0,0))
	,m_shaderProgram("Shaders/simpleVertex.vert", "Shaders/simpleFragment.frag")
{
}

GameObject::GameObject(glm::vec3 pos)
	:m_position(pos)
	,m_rotation(glm::vec3(0,0,0))
	,m_scale(glm::vec3(1,1,1))
	,m_shaderProgram("Shaders/simpleVertex.vert", "Shaders/simpleFragment.frag")
{
}

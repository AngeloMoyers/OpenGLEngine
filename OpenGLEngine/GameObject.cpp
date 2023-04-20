#include "GameObject.h"

//#include "STB.h"

#define TEST 2

#if TEST == 2
std::vector<float> vertices = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
#elif TEST == 1

std::vector<float> vertices = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};
#endif



GameObject::GameObject(glm::vec3 pos)
	: m_position(pos)
	, m_forward(glm::vec3(0, 0, -1))
	, m_rotation(0.0f,0.0f,0.0f)
	, m_scale(glm::vec3(1, 1, 1))
{
	/*m_shaderProgram.SetInt("uMaterial.diffuse", 0);
	m_shaderProgram.SetInt("uMaterial.specular", 1);
	m_shaderProgram.SetVec3("uMaterial.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shaderProgram.SetFloat("uMaterial.shininess", 32.0f);

	m_shaderProgram.SetVec3("uPLight[0].ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shaderProgram.SetVec3("uPLight[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shaderProgram.SetVec3("uPLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shaderProgram.SetFloat("uPLight[0].constant", 1.0f);
	m_shaderProgram.SetFloat("uPLight[0].linear", 0.09f);
	m_shaderProgram.SetFloat("uPLight[0].quadratic", 0.032f);

	m_shaderProgram.SetVec3("uDLight.ambient", glm::vec3(0.01f, 0.01f, 0.01f));
	m_shaderProgram.SetVec3("uDLight.diffuse", glm::vec3(0.01f, 0.01f, 0.01f));
	m_shaderProgram.SetVec3("uDLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	m_shaderProgram.SetVec3("uSLight.ambient", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shaderProgram.SetVec3("uSLight.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	m_shaderProgram.SetVec3("uSLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	m_shaderProgram.SetFloat("uSLight.constant", 1.0f);
	m_shaderProgram.SetFloat("uSLight.linear", 0.09f);
	m_shaderProgram.SetFloat("uSLight.quadratic", 0.032f);*/
}

GameObject::GameObject(glm::vec3 pos, const char* modelPath, const char* vertexShaderPath, const char* fragmentShaderPath)
	: m_position(pos)
	, m_forward(glm::vec3(0, 0,-1))
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(glm::vec3(1, 1, 1))
{
	SetModel(std::make_shared<Model>(this, modelPath, vertexShaderPath, fragmentShaderPath));
}

GameObject::~GameObject()
{

}

glm::mat4 GameObject::ModelMatrix()
{
	glm::mat4 mat = glm::mat4(1.0f);
	glm::mat4 rot = glm::rotate(mat, glm::radians(m_rotation.x), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(mat, glm::radians(m_rotation.y), glm::vec3(0.0, 1.0, 0.0)) * glm::rotate(mat, glm::radians(m_rotation.z), glm::vec3(0.0, 0.0, 1.0));
	mat = glm::translate(mat, m_position) * rot * glm::scale(mat, m_scale);

	return mat;
}

void GameObject::SetRotation(glm::vec3 rot)
{
	m_rotation = rot;

	m_forward.x = cos(glm::radians(rot.x)) * cos(glm::radians(rot.y));
	m_forward.y = sin(glm::radians(rot.y));
	m_forward.z = sin(glm::radians(rot.x)) * cos(glm::radians(rot.y));
}

void GameObject::SetForwardDirection(glm::vec3 rot)
{
	m_forward = rot;

	m_rotation.y = glm::degrees(-asin(glm::dot(m_forward, glm::vec3(0.0f, 1.0f, 0.0f))));
	glm::vec3 normForward = normalize(glm::vec3(m_forward.x, 0.0f, m_forward.z));
	m_rotation.x = glm::degrees(acos(dot(normForward, glm::vec3(1.0f, 0.0f, 0.0f))));
}

void GameObject::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	if (m_pModel !=  nullptr)
		m_pModel->Draw(projectionMatrix, viewMatrix, ModelMatrix());
}

void GameObject::Update(float deltaTime)
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Update(deltaTime);
	}
}

void GameObject::Destroy()
{
	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->Destroy();
	}
}


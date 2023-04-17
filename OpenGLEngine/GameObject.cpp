#include "GameObject.h"

#include "STB.h"

std::vector<float> vertices = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

GameObject::GameObject()
	:m_position(glm::vec3(0,0,0))
	,m_shaderProgram("Shaders/simpleVertex.vert", "Shaders/simpleFragment.frag")
	,m_model(glm::mat4(1.0f))
{
	m_model = glm::translate(m_model, m_position);

	SetVertices(vertices);
	InitTexture();
	InitMesh();
}

GameObject::GameObject(glm::vec3 pos, bool useShader)
	: m_position(pos)
	, m_forward(glm::vec3(0, 0, 1))
	, m_scale(glm::vec3(1, 1, 1))
	, m_shaderProgram("Shaders/simpleVertex.vert", "Shaders/simpleFragment.frag")
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);

	m_shaderProgram.Use();
	m_shaderProgram.SetInt("tex", 0);
	m_shaderProgram.SetInt("tex2", 1);

	SetVertices(vertices);
	InitTexture();
	InitMesh();
}

GameObject::~GameObject()
{

}

glm::mat4 GameObject::Model()
{
	m_model = glm::mat4(1.0f);
	m_model = glm::translate(m_model, m_position);
	m_model = glm::lookAt(m_position, m_position + m_forward, glm::vec3(0.0, 1.0, 0.0));

	return m_model;
}

void GameObject::SetVertices(float verts[])
{
	int size = (sizeof(verts) / sizeof(verts[0]));
	m_vertices = std::vector<float>(verts, verts + size);
}

void GameObject::SetVertices(std::vector<float> verts)
{
	m_vertices = verts;
}

void GameObject::Update()
{
}

void GameObject::Destroy()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_elementBufferObject);
	glDeleteBuffers(1, &m_vertexBufferObject);

	m_shaderProgram.Destroy();
}

void GameObject::InitMesh()
{
	glGenVertexArrays(1, &m_vertexArrayObject);
	glGenBuffers(1, &m_vertexBufferObject);
	glGenBuffers(1, &m_elementBufferObject);

	if (m_vertices.size() > 0)
	{
		glBindVertexArray(m_vertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	if (m_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), &m_indices[0], GL_STATIC_DRAW);
	}

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void GameObject::InitTexture()
{
	stbi_set_flip_vertically_on_load(true);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int imgWidth, imgHeight, nrChannels;
	unsigned char* imgData = stbi_load("Textures/Example1.jpg", &imgWidth, &imgHeight, &nrChannels, 0);

	int imgWidth2, imgHeight2, nrChannels2;
	unsigned char* imgData2 = stbi_load("Textures/Example5.jpg", &imgWidth2, &imgHeight2, &nrChannels2, 0);

	unsigned int texID, texID2;
	glGenTextures(1, &texID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenTextures(1, &texID2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texID2);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth2, imgHeight2, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData2);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imgData);
	stbi_image_free(imgData2);

	m_textureIDs.push_back(texID);
	m_textureIDs.push_back(texID2);
}

void GameObject::UpdateTransform()
{
	/*glm::vec3 front;
	front.x = cos(glm::radians(-90.0f)) * cos(glm::radians(0.0f));
	front.y = sin(glm::radians(0.0f));
	front.z = sin(glm::radians(-90.0f)) * cos(glm::radians(0.0f));
	m_forward = glm::normalize(front);*/
}

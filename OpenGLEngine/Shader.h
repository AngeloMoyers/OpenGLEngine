#pragma once

#include <glad/glad.h>

//stl
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int m_programID;

	std::string m_vertexPath;
	std::string m_fragmentPath;

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	unsigned int GetProgramID() { return m_programID; }

	//uniforms
	void SetBool(const std::string name, bool value) const;
	void SetInt(const std::string name, int value) const;
	void SetFloat(const std::string name, float value) const;
	void SetMat4(const std::string name, glm::mat4 value) const;
};


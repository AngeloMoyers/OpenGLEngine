#include "Shader.h"

#include <stdexcept>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
	:m_vertexPath(vertexPath), m_fragmentPath(fragmentPath)
{
	std::string vertCode;
	std::string fragCode;
	std::ifstream vFile;
	std::ifstream fFile;

	vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vFile.open(vertexPath);
		fFile.open(fragmentPath);
		std::stringstream vStream, fStream;

		vStream << vFile.rdbuf();
		fStream << fFile.rdbuf();

		vFile.close();
		fFile.close();

		vertCode = vStream.str();
		fragCode = fStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader files not succesfully read!" << std::endl;
	}

	const char* vSource = vertCode.c_str();
	const char* fSource = fragCode.c_str();

	unsigned int vertID, fragID;
	int success;
	char infoLog[512];

	vertID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertID, 1, &vSource, NULL);
	glCompileShader(vertID);

	glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertID, 512, NULL, infoLog);
		throw std::runtime_error("Failed to compile vertex shader: " + *infoLog);
	}

	fragID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragID, 1, &fSource, NULL);
	glCompileShader(fragID);

	glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragID, 512, NULL, infoLog);
		throw std::runtime_error("Failed to compile fragment shader: " + *infoLog);
	}

	//program
	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertID);
	glAttachShader(m_programID, fragID);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		throw std::runtime_error("Failed to link shader program: " + *infoLog);
	}

	glDeleteShader(vertID);
	glDeleteShader(fragID);
}

void Shader::Use()
{
	glUseProgram(m_programID);
}

void Shader::SetBool(const std::string name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetFloat(const std::string name, float value) const
{
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}

void Shader::SetMat4(const std::string name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

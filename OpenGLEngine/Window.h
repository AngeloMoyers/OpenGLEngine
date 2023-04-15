#pragma once

//GL
#include <glad/glad.h>
#include "GLFW/glfw3.h"


//stl
#include <iostream>
#include <memory>

class Window
{
private:
	const int m_width;
	const int m_height;

	GLFWwindow* m_pWindow;
public:
	Window(const int width, const int height);
	~Window();

private:
	void Init(const int width, const int height);
	void HandleInput(GLFWwindow* window);
	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

public:
	void Run(unsigned int shaderProgramID, unsigned int vertexArrayObjectID, unsigned int* textureID);
	GLFWwindow* GetWindow() { return m_pWindow; }
};


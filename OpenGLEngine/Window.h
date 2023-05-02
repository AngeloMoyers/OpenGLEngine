#pragma once

#include "Camera.h"

//GL
#include <glad/glad.h>
#include "GLFW/glfw3.h"


//stl
#include <iostream>
#include <memory>

class Scene;

class Window
{
private:
	const int m_width;
	const int m_height;

	glm::vec4 m_ambientLighting;

	GLFWwindow* m_pWindow;

	std::unique_ptr<Scene> m_pScene;

	static glm::vec2 m_mousePos;
	static float m_fov;
public:
	Window(const int width, const int height);
	~Window();

private:
	void Init(const int width, const int height);
	void HandleInput(GLFWwindow* window, Camera* mainCam);
	static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);

	static void RetrieveMouseInput(GLFWwindow* pWindow, double xPos, double yPos);
	static void RetrieveScrollInput(GLFWwindow* pWindow, double xOffset, double yOffset);
public:
	void Run();
	GLFWwindow* GetWindow() { return m_pWindow; }
};


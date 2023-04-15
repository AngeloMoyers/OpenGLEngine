#include "Window.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Window::Window(const int width, const int height)
	:m_width(width), m_height(height)
{
	Init(width, height);
}

Window::~Window()
{
	glfwTerminate();
}

void Window::Init(const int width, const int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(800, 600, "My First OpenGL Window", NULL, NULL);
	if (m_pWindow == NULL)
	{
		glfwTerminate();
		std::runtime_error("Failed to create a window!");
		return;
	}
	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow, Window::FramebufferResizeCallback); 

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwTerminate();
		std::runtime_error("Failed to initiaize GLAD");
		return;
	}

	glEnable(GL_DEPTH_TEST);
}

void Window::HandleInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Window::FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::Run(unsigned int shaderProgramID, unsigned int vertexArrayObjectID, unsigned int* textureID)
{

	glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f );
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

	glm::vec3 up = glm::vec3(0.0, 1.0, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f) };

	float rotateRadius = 10.0f;
	float camX = sin(glfwGetTime()) * rotateRadius;
	float camY = cos(glfwGetTime()) * rotateRadius;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		//input
		HandleInput(m_pWindow);

		glClearColor(0.0f, 0.6f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use program
		glUseProgram(shaderProgramID);

		float rotateRadius = 10.0f;
		float camX = sin(glfwGetTime()) * rotateRadius;
		float camY = cos(glfwGetTime()) * rotateRadius;
		view = glm::lookAt(glm::vec3(camX, 0.0, camY), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		int uViewLocation = glGetUniformLocation(shaderProgramID, "view");
		glUniformMatrix4fv(uViewLocation, 1, GL_FALSE, glm::value_ptr(view));

		int uProjectionLocation = glGetUniformLocation(shaderProgramID, "projection");
		glUniformMatrix4fv(uProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		/*int uTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
		glUniformMatrix4fv(uTransformLocation, 1, GL_FALSE, glm::value_ptr(trans));*/

		int uTimeLocation = glGetUniformLocation(shaderProgramID, "uTime");
		glUniform1f(uTimeLocation, glfwGetTime());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID[0]);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureID[1]);
		glBindVertexArray(vertexArrayObjectID);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		for (int i = 0; i < 3; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f * i*i + 1), glm::vec3(0.5f, 1.0f, 0.0f));

			int uModelLocation = glGetUniformLocation(shaderProgramID, "model");
			glUniformMatrix4fv(uModelLocation, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
			
		//Poll Events and swap buffers
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}

#include "Window.h"

#include "GameObject.h"
#include "Camera.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec2 Window::m_mousePos = glm::vec2(0.0f, 0.0f); //TODO: this is unnecessary
float Window::m_fov = 45.0f;

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
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(m_pWindow, RetrieveMouseInput);
	glfwSetScrollCallback(m_pWindow, RetrieveScrollInput);
}

void Window::HandleInput(GLFWwindow* window, Camera* mainCam)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 0.05f; //
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mainCam->SetPosition(mainCam->GetPosition() + (mainCam->Forward() * cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCam->SetPosition(mainCam->GetPosition() - (mainCam->Forward() * cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCam->SetPosition(mainCam->GetPosition() - (mainCam->Right() * cameraSpeed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCam->SetPosition(mainCam->GetPosition() + (mainCam->Right() * cameraSpeed));
}

void Window::FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::RetrieveMouseInput(GLFWwindow* pWindow, double xPos, double yPos)
{
	m_mousePos = glm::vec2(xPos, yPos);
}

void Window::RetrieveScrollInput(GLFWwindow* pWindow, double xOffset, double yOffset)
{
	m_fov -= (float)yOffset;
	if (m_fov < 1.0f)
		m_fov = 1.0f;
	if (m_fov > 45.0f)
		m_fov = 45.0f;
}

void Window::Run()
{

	std::vector<GameObject> cubes;

	cubes.emplace_back(glm::vec3(0.0f,0.0f,0.0f));
	cubes.emplace_back(glm::vec3(0.0f,1.0f,3.0f));
	cubes.emplace_back(glm::vec3(-8.0f,1.0f,2.5f));

	Camera cam = Camera(glm::vec2(m_width, m_height));
	cam.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	cam.SetForwardDirection(glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 projection;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		//input
		HandleInput(m_pWindow, &cam);
		cam.UpdateMouseInput(m_mousePos);
		cam.SetFOV(m_fov);
		
		projection = glm::perspective(glm::radians(cam.GetFOV()), (float)m_width / (float)m_height, 0.1f, 100.0f);

		glClearColor(0.0f, 0.6f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		//Orbit Camera
		float rotateRadius = 30.0f;
		float camX = sin(glfwGetTime()) * rotateRadius;
		float camY = cos(glfwGetTime()) * rotateRadius;

		for (int i = 0; i < cubes.size(); i++) //TODO: abstract out, objects draw themselves
		{
			cubes[i].GetShader().Use();

			int uViewLocation = glGetUniformLocation(cubes[i].GetShader().GetProgramID(), "view");
			glUniformMatrix4fv(uViewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetView()));

			int uProjectionLocation = glGetUniformLocation(cubes[i].GetShader().GetProgramID(), "projection");
			glUniformMatrix4fv(uProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

			int uTimeLocation = glGetUniformLocation(cubes[i].GetShader().GetProgramID(), "uTime");
			glUniform1f(uTimeLocation, glfwGetTime());

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, cubes[i].GetTextures()[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, cubes[i].GetTextures()[1]);
			glBindVertexArray(cubes[i].VAO());
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			cubes[i].GetShader().SetMat4("model", cubes[i].Model());

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
			
		//Poll Events and swap buffers
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}

	for (int i = 0; i < cubes.size(); i++)
	{
		cubes[i].Destroy();
	}
}

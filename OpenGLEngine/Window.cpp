#include "Window.h"

#include "GameObject.h"
#include "Camera.h"
#include "Model.h"

#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec2 Window::m_mousePos = glm::vec2(0.0f, 0.0f); //TODO: this is unnecessary
float Window::m_fov = 45.0f;

Window::Window(const int width, const int height)
	:m_width(width), m_height(height)
	,m_ambientLighting(glm::vec4(0.8f, 0.8f,1.0f,0.5f))
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

	m_pWindow = glfwCreateWindow(width, height, "My First OpenGL Window", NULL, NULL);
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

	std::vector<GameObject*> objects;

	GameObject light(glm::vec3(3.0f, 0.0, 0.0f),  "Models/backpack/backpack.obj", "Shaders/simpleVertex.vert", "Shaders/lightFragment.frag");
	light.SetScale(glm::vec3(0.5f));
	light.SetRotation(glm::vec3(0.0f, 90.0f, 45.0f));

	objects.push_back(&light);


	GameObject bp = GameObject(glm::vec3(0.0, 0.0, 0.0), "Models/backpack/backpack.obj", "Shaders/simpleVertex.vert", "Shaders/simpleFragment.frag");
	objects.push_back(&bp);

	Camera cam = Camera(glm::vec2(m_width, m_height));
	cam.SetPosition(glm::vec3(0.0f, 0.0f, 10.0f));
	cam.SetForwardDirection(glm::vec3(0.0f, 0.0f, -1.0f));

	glm::mat4 projection;

	float lastFrameTime = glfwGetTime();
	float currentFrametime = lastFrameTime;;

	while (!glfwWindowShouldClose(m_pWindow))
	{
		currentFrametime = glfwGetTime();
		float deltaTime =currentFrametime - lastFrameTime;
		lastFrameTime = currentFrametime;

		//input
		HandleInput(m_pWindow, &cam);
		cam.UpdateMouseInput(m_mousePos);
		cam.SetFOV(m_fov);

		bp.SetRotation(glm::vec3(0.0, 30 * glm::sin(glfwGetTime()), 0.0));
		
		projection = glm::perspective(glm::radians(cam.GetFOV()), (float)m_width / (float)m_height, 0.1f, 100.0f);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(deltaTime);
			objects[i]->Draw(projection, cam.GetView());
		}
		
		//Poll Events and swap buffers
		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Destroy();
	}
}

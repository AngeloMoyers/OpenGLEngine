
#include "Window.h"
#include "Shader.h"
#include "GameObject.h"

//stl
#include <iostream>
#include <stdexcept>

//libs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{

	Window window(800, 600);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	window.Run();

	glfwTerminate();

	return 0;
}


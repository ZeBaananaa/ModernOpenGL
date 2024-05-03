#include "Utils/WindowHandler.h"
#include <glad/glad.h>

void WindowHandler::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	Camera::Get().recalculateProjection = true;
}

void WindowHandler::BufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
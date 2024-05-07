#include "Utils/WindowHandler.h"
#include "App.h"

void WindowHandler::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	Application::Get().m_width = width;
	Application::Get().m_height = height;
	Camera::Get().recalculateProjection = true;
}

void WindowHandler::BufferResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
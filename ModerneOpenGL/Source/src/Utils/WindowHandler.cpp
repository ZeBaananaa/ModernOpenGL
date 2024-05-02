#include "Utils/WindowHandler.h"

Vector2D WindowHandler::currentWindowSize = Vector2D(1280, 720);

void WindowHandler::WindowResizeCallback(GLFWwindow* window, int width, int height)
{
	currentWindowSize = Vector2D(width, height);

	Camera::Get().recalculateProjection = true;
}
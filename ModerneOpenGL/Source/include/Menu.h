#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "App.h"

class Menu
{
public:
	~Menu() = default;

	static Menu& Get();
	static void Destroy();
	void Init();
	void Render();
	void Update();

private:
	Menu() = default;

	static Menu* instance;
};
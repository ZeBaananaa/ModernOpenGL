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
	void Draw();

	void DrawRoot();
	void DrawChildren(Transform* child);
	static void DrawChildSettings(Transform* child);

private:
	Menu() = default;
	static Menu* instance;

	Transform* latestChildClicked;
};
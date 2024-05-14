#include "Menu.h"

Menu* Menu::instance = nullptr;

Menu& Menu::Get()
{
	if (instance == nullptr)
		instance = new Menu();
	return *instance;
}

void Menu::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void Menu::Init()
{
	// IMGUI INIT
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(Application::Get().window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void Menu::Render()
{
	// Init imgui window
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Rendering
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGuiWindowFlags_AlwaysAutoResize;
}

void Menu::Update()
{
}

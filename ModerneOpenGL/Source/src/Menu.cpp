#include "Menu.h"
#include "SceneGraph.h"

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
	ImGui_ImplOpenGL3_Init("#version 330");;
}

void Menu::Render()
{
	// Init imgui window
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Rendering
	Draw();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(400.f, 250.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Once);

	// Object Tree Window
	if (ImGui::Begin("Object Tree"), ImGuiWindowFlags_AlwaysAutoResize)
		if (ImGui::CollapsingHeader("Scene"))
			DrawRoot();

	if (latestChildClicked != nullptr)
		DrawChildSettings(latestChildClicked);
	
	ImGui::End();
}

void Menu::DrawRoot()
{
	ImGui::Indent(20.0f);

	for (auto ch = SceneGraph::Get().root->GetChildren().begin(); ch != SceneGraph::Get().root->GetChildren().end(); ++ch)
	{
		if (ImGui::CollapsingHeader(((*ch)->GetName()).c_str()))
		{
			ImGui::Indent(20.0f);
			ImGui::Button(((*ch)->GetName()).c_str());

			if (ImGui::IsItemClicked())
				latestChildClicked = *ch;
			
			DrawChildren((*ch));
		}
	}

	ImGui::Unindent(20.0f);
}

void Menu::DrawChildren(Transform* child)
{
	ImGui::Indent(20.0f);

	for (auto ch = child->GetChildren().begin(); ch != child->GetChildren().end(); ++ch)
	{
		if (!(*ch)->GetChildren().empty())
			ImGui::CollapsingHeader(((*ch)->GetName()).c_str());
		else
		{
			ImGui::Button(((*ch)->GetName()).c_str());
			if (ImGui::IsItemClicked())
				latestChildClicked = *ch;
		}
		DrawChildren((*ch));
	}

	ImGui::Unindent(20.0f);
}

void Menu::DrawChildSettings(Transform* child)
{
	std::string title = "Object Inspector : " + child->GetName() + "###inspector";
	ImGui::SetNextWindowSize(ImVec2(400.f, 250.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0.f, 275.f), ImGuiCond_Once);

	if (ImGui::Begin(title.c_str()), ImGuiWindowFlags_AlwaysAutoResize)
	{
		Vector3D translationF = child->GetLocalPosition();
		Vector3D rotationF = child->GetLocalRotation();
		Vector3D scalingF = child->GetLocalScale();

		ImGui::DragFloat3(("translationXY##" + child->GetName()).c_str(), &translationF[0], 0.1f);
		ImGui::DragFloat3(("rotationXYZ##" + child->GetName()).c_str(), &rotationF[0], 0.1f);
		ImGui::DragFloat3(("scalingXYZ##" + child->GetName()).c_str(), &scalingF[0], 0.1f, 0.2f);

		if (translationF != child->GetLocalPosition())
			child->SetLocalPosition(translationF);

		if (rotationF != child->GetLocalRotation())
			child->SetLocalRotation(rotationF);

		if (scalingF != child->GetLocalScale())
			child->SetLocalScale(scalingF);
	} ImGui::End();
}
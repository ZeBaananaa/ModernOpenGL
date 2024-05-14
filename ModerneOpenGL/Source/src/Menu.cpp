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
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGuiWindowFlags_AlwaysAutoResize;
}

void Menu::Render()
{
	// Init imgui window
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Rendering
	Draw();
	//ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Menu::Draw()
{
	if (ImGui::Begin("Object Tree"))
	{
		if(ImGui::CollapsingHeader("Scene"))
			DrawRoot();
	}
	ImGui::End();
}

void Menu::DrawRoot()
{
    ImGui::Indent(20.0f);

    for (auto ch = SceneGraph::Get().root->GetChildren().begin(); ch != SceneGraph::Get().root->GetChildren().end(); ++ch)
    {
        if (ImGui::CollapsingHeader(((*ch)->GetName()).c_str()))
			DrawChildren((*ch));
    }

    ImGui::Unindent(20.0f);
}

void Menu::DrawChildren(Transform* child)
{
	child->GetName();

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

    ImGui::Indent(20.0f);

    for (auto ch = child->GetChildren().begin(); ch != child->GetChildren().end(); ++ch)
    {
        if (ImGui::CollapsingHeader(((*ch)->GetName()).c_str()))
			DrawChildren((*ch));
    }

    ImGui::Unindent(20.0f);
}
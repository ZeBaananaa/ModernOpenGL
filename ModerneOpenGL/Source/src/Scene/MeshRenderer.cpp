#include "MeshRenderer.h"
#include "ResourcesManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "App.h"

MeshRenderer::MeshRenderer(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

MeshRenderer::MeshRenderer(GameObject* gameObject,std::string modelName)
{
	this->gameObject = gameObject;
	this->model = ResourceManager::Get().Get<Model>(modelName);
}

MeshRenderer::~MeshRenderer()
{
	model = nullptr;
	gameObject = nullptr;
}

void MeshRenderer::Update()
{
	if (model)
	{
		model->vertexAttributes.Bind();
		MVP = Camera::Get().GetVPMatrix() * gameObject->transform->GetGlobalTransform();

		glUniformMatrix4fv(glGetUniformLocation(Application::Get().shader.GetProgram(), "MVP"), 1, false, &MVP.col1.x); // True = transposed

		glDrawElements(GL_TRIANGLES, model->indexes.size(), GL_UNSIGNED_INT, 0);
	}
}

void MeshRenderer::Delete()
{
	delete this;
}
